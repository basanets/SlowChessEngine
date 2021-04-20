#include "DefaultSearcher.h"

#include <MoveGeneration/MoveList.h>
#include <BoardRepresentation/Position.h>
#include <Evaluation/SimpleEvaluator.h>
#include <chrono>
#include <stdexcept>

static constexpr int32_t positiveInfinity = 100000;
static constexpr int32_t negativeInfinity = -positiveInfinity;
static constexpr int32_t checkmateScore = 10000;

std::tuple<Move, int32_t> DefaultSearcher::iterativeDeepeningSearch(const Position & position, uint32_t maxDepth)
{
    timeTaken = 0;
    nodesReached = 0;
    nodesEvaluated = 0;
    nodesCutOff = 0;

    auto start = std::chrono::high_resolution_clock::now();

    std::tuple<Move, int32_t> result;
    for (uint32_t depth = 1; depth <= maxDepth; ++depth)
    {
        result = findBestMove(position, depth);
        std::tie(knownBestMove, std::ignore) = result;
    }

    auto finish = std::chrono::high_resolution_clock::now();
    timeTaken = std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();

    return result;
}

std::tuple<Move, int32_t> DefaultSearcher::findBestMove(const Position & position, uint32_t depth)
{
    if (depth == 0)
        throw std::runtime_error("Cannot find any moves at depth 0");

    std::tuple<Move, int32_t> bestMove = {Move(NULL_SQUARE, NULL_SQUARE), negativeInfinity};

    Position copiedPosition = position;
    MoveList moveList(copiedPosition);
    orderMoves(moveList, position, knownBestMove);

    int32_t alpha = negativeInfinity;
    for (Move move: moveList)
    {
        copiedPosition.makeMove(move);
        // since we don't know other beta's here yet
        int32_t evaluation = -search(copiedPosition, depth - 1, 1, negativeInfinity, -alpha);
        copiedPosition.undoMove(move);

        if (evaluation > alpha)
        {
            alpha = evaluation;
            bestMove = {move, evaluation};
        }
    }

    return bestMove;
}

int32_t DefaultSearcher::search(Position & position, uint32_t depth, uint32_t plyFromRoot, int32_t alpha, int32_t beta)
{
    if (depth == 0)
    {
        return quiescenceSearch(position, plyFromRoot, alpha, beta);
    }

    ++nodesReached;

    if (position.history[position.gamePly].plyFiftyMoveRule == 50)
    {
        // draw;
        return 0;
    }

    MoveList moveList(position);
    moveList.orderMoves(position);
    if (moveList.size() == 0)
    {
        if (position.getCheckers() != 0)
        {
            // checkmate, subtract the ply because the earlier checkmate the better
            return -(checkmateScore - plyFromRoot * 10);
        }

        // stalemate
        return 0;
    }

    for (Move move: moveList)
    {
        position.makeMove(move);
        int32_t evaluation = -search(position, depth - 1, plyFromRoot + 1, -beta, -alpha);
        position.undoMove(move);

        // move is TOO good
        if (evaluation >= beta)
        {
            ++nodesCutOff;
            return beta;
        }

        if (evaluation > alpha)
        {
            alpha = evaluation;
        }
    }

    return alpha;
}

// simplified quiescence search
int32_t DefaultSearcher::quiescenceSearch(Position & position, uint32_t plyFromRoot, int32_t alpha, int32_t beta)
{
    ++nodesEvaluated;
    ++nodesReached;

    int evaluation = SimpleEvaluator::evaluate(position, position.sideToPlay);
    if (evaluation >= beta)
    {
        // cut off
        ++nodesCutOff;
        return beta;
    }

    if (evaluation > alpha)
    {
        alpha = evaluation;
    }

    MoveList moveList(position);
    if (moveList.size() == 0)
    {
        if (position.getCheckers() != 0)
        {
            // checkmate, subtract the ply because the earlier checkmate the better
            return -(checkmateScore - plyFromRoot * 10);
        }

        // stalemate
        return 0;
    }

    for (Move move: moveList)
    {
        if (!move.isCapture()) continue;

        position.makeMove(move);
        evaluation = -quiescenceSearch(position, plyFromRoot + 1, -beta, -alpha);
        position.undoMove(move);

        if (evaluation >= beta)
        {
            ++nodesCutOff;
            return beta;
        }

        if (evaluation > alpha)
        {
            alpha = evaluation;
        }
    }

    return alpha;
}

void DefaultSearcher::orderMoves(MoveList & moveList, const Position & pos, Move bestMove)
{
    moveList.orderMoves(pos);

    // set the move we know is best to this move
    if (bestMove.isValid())
    {
        Move * move = std::find(moveList.begin(), moveList.end(), bestMove);
        if (move != moveList.end())
        {
            std::iter_swap(moveList.begin(), move);
        }
    }
}

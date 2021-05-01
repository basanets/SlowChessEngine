#include "PrincipalVariationSearcher.h"

#include <Evaluation/NeuralNetworkEvaluator.h>
#include <Evaluation/SimpleEvaluator.h>

static constexpr int32_t positiveInfinity = 100000;
static constexpr int32_t negativeInfinity = -positiveInfinity;
static constexpr int32_t checkmateScore = 10000;

PrincipalVariationSearcher::PrincipalVariationSearcher(NeuralNetworkEvaluator * nnEvaluator)
    : nnEvaluator(nnEvaluator)
{
    constexpr uint32_t MAX_SEARCH_DEPTH = 256;
    principalVariation.resize(MAX_SEARCH_DEPTH, Move());
}

std::tuple<Move, int32_t> PrincipalVariationSearcher::iterativeDeepeningSearch(const Position & position, uint32_t maxDepth)
{
    maxReachedDepth = 0;
    std::tuple<Move, int32_t> result;
    for (uint32_t depth = 1; depth <= maxDepth; ++depth)
    {
        result = findBestMove(position, depth);
    }
    return result;
}

std::tuple<Move, int32_t> PrincipalVariationSearcher::findBestMove(const Position & position, uint32_t depth)
{
    if (depth == 0)
        throw std::runtime_error("Cannot find any moves at depth 0");

    std::tuple<Move, int32_t> bestMove = {Move(NULL_SQUARE, NULL_SQUARE), negativeInfinity};

    Position copiedPosition = position;
    MoveList moveList(copiedPosition);
    orderMoves(moveList, copiedPosition, 0);

    int32_t alpha = negativeInfinity;
    for (Move move: moveList)
    {
        copiedPosition.makeMove(move);
        int32_t evaluation = -search(copiedPosition, depth - 1, 1, negativeInfinity, -alpha);
        copiedPosition.undoMove(move);

        if (evaluation > alpha)
        {
            alpha = evaluation;
            bestMove = {move, evaluation};
            principalVariation[0] = move;
        }
    }

    return bestMove;
}

int32_t PrincipalVariationSearcher::search(Position & position, uint32_t depth, uint32_t plyFromRoot, int32_t alpha, int32_t beta)
{
    maxReachedDepth = std::max(maxReachedDepth, plyFromRoot);
    if (depth == 0)
    {
        return quiescenceSearch(position, plyFromRoot, alpha, beta);
    }

    if (position.history[position.gamePly].plyFiftyMoveRule == 50)
    {
        // draw;
        return 0;
    }

    MoveList moveList(position);
    orderMoves(moveList, position, plyFromRoot);
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

        if (evaluation >= beta)
        {
            // move is TOO good
            return beta;
        }

        if (evaluation > alpha)
        {
            alpha = evaluation;
            principalVariation[plyFromRoot] = move;
        }
    }

    return alpha;
}

int32_t PrincipalVariationSearcher::quiescenceSearch(Position & position, uint32_t plyFromRoot, int32_t alpha, int32_t beta)
{
    maxReachedDepth = std::max(maxReachedDepth, plyFromRoot);
    int evaluation = this->evaluatePosition(position);
    if (evaluation >= beta)
    {
        return beta;
    }

    if (evaluation > alpha)
    {
        alpha = evaluation;
    }

    MoveList moveList(position);
    orderMoves(moveList, position, plyFromRoot);
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
            return beta;
        }

        if (evaluation > alpha)
        {
            alpha = evaluation;
            principalVariation[plyFromRoot] = move;
        }
    }

    return alpha;
}

int32_t PrincipalVariationSearcher::evaluatePosition(const Position & position)
{
    if (nnEvaluator == nullptr)
    {
        return SimpleEvaluator::evaluate(position, position.sideToPlay);
    }
    else
    {
        return nnEvaluator->evaluate(position, position.sideToPlay);
    }
}

void PrincipalVariationSearcher::orderMoves(MoveList & moveList, const Position & pos, uint32_t plyFromRoot)
{
    moveList.orderMoves(pos);

    // set the move we know is best to this move
    Move bestMove = principalVariation[plyFromRoot];
    if (bestMove.isValid())
    {
        Move * move = std::find(moveList.begin(), moveList.end(), bestMove);
        if (move != moveList.end())
        {
            std::iter_swap(moveList.begin(), move);
        }
    }
}

uint32_t PrincipalVariationSearcher::getMaxDepth() const
{
    return maxReachedDepth;
}

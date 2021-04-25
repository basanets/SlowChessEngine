#ifndef DEFAULTSEARCHER_H
#define DEFAULTSEARCHER_H

class Position;
class Move;

#include "CoreConfig.h"

#include <vector>
#include <inttypes.h>
#include <tuple>

#include <BoardRepresentation/Color.h>
#include <MoveGeneration/MoveList.h>

class NeuralNetworkEvaluator;

class DefaultSearcher
{
public:
    uint64_t timeTaken;
    uint32_t nodesReached;
    uint32_t nodesEvaluated;
    uint32_t nodesCutOff;

public:
    explicit DefaultSearcher(NeuralNetworkEvaluator * nnEvaluator = nullptr);
private:
    NeuralNetworkEvaluator * nnEvaluator;

public:
    std::tuple<Move, int32_t> iterativeDeepeningSearch(const Position & position, uint32_t maxDepth);
    std::tuple<Move, int32_t> findBestMove(const Position & position, uint32_t depth);
    int32_t search(Position & position, uint32_t depth, uint32_t plyFromRoot, int32_t alpha, int32_t beta);
    int32_t quiescenceSearch(Position & position, uint32_t plyFromRoot, int32_t alpha, int32_t beta);
    int32_t evaluatePosition(const Position & position);

private:
    Move knownBestMove = Move(NULL_SQUARE, NULL_SQUARE);
    void orderMoves(MoveList & moveList, const Position & pos, Move bestMove = Move(NULL_SQUARE, NULL_SQUARE));
};

#endif // DEFAULTSEARCHER_H

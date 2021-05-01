#ifndef PRINCIPALVARIATIONSEARCHER_H
#define PRINCIPALVARIATIONSEARCHER_H

#include <tuple>
#include <BoardRepresentation/Position.h>
#include <MoveGeneration/MoveList.h>
class NeuralNetworkEvaluator;

class PrincipalVariationSearcher
{
public:
    explicit PrincipalVariationSearcher(NeuralNetworkEvaluator * nnEvaluator = nullptr);

public:
    std::tuple<Move, int32_t> iterativeDeepeningSearch(const Position & position, uint32_t maxDepth);
    std::tuple<Move, int32_t> findBestMove(const Position & position, uint32_t depth);

    int32_t search(Position & position, uint32_t depth, uint32_t plyFromRoot, int32_t alpha, int32_t beta);
    int32_t quiescenceSearch(Position & position, uint32_t plyFromRoot, int32_t alpha, int32_t beta);
    int32_t evaluatePosition(const Position & position);

    uint32_t getMaxDepth() const;

private:
    void orderMoves(MoveList & moveList, const Position & pos, uint32_t plyFromRoot);

    NeuralNetworkEvaluator * nnEvaluator;
    std::vector<Move> principalVariation;
    uint32_t maxReachedDepth = 0;
};

#endif // PRINCIPALVARIATIONSEARCHER_H

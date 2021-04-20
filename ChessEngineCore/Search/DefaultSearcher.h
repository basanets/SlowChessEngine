#ifndef DEFAULTSEARCHER_H
#define DEFAULTSEARCHER_H

class Position;
class Move;
#include <vector>
#include <inttypes.h>
#include <tuple>

class DefaultSearcher
{
public:
    uint64_t timeTaken;
    uint32_t nodesReached;
    uint32_t nodesEvaluated;
    uint32_t nodesCutOff;

public:
    std::tuple<Move, int32_t> findBestMove(const Position & position, uint32_t depth);
    int32_t search(Position & position, uint32_t depth, uint32_t plyFromRoot, int32_t alpha, int32_t beta);
    int32_t quiescenceSearch(Position & position, uint32_t plyFromRoot, int32_t alpha, int32_t beta);
};

#endif // DEFAULTSEARCHER_H
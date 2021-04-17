#include "PerfomanceTester.h"
#include "../BoardRepresentation/Position.h"
#include "../MoveGeneration/MoveList.h"

#include <iostream>

uint64_t PerfomanceTester::perft(Position & pos, uint32_t depth)
{
    if (depth == 0) return 1;

    MoveList moveList(pos);
    if (depth == 1) return moveList.size();

    uint64_t nodes = 0;
    for (Move move: moveList)
    {
        pos.makeMove(move);
        nodes += perft(pos, depth - 1);
        pos.undoMove(move);
    }

    return nodes;
}

uint64_t PerfomanceTester::perftdiv(Position & pos, uint32_t depth)
{
    if (depth == 0)
        return 1;

    MoveList moveList(pos);
    uint64_t totalNodes = 0;

    for (Move move: moveList)
    {
        pos.makeMove(move);
        uint64_t nodes = perft(pos, depth - 1);
        pos.undoMove(move);

        std::cout << move.toString() << ": " << nodes << std::endl;
        totalNodes += nodes;
    }

    return totalNodes;
}

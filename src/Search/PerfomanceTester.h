#ifndef PERFOMANCETESTER_H
#define PERFOMANCETESTER_H

class Position;
#include <inttypes.h>

class PerfomanceTester
{
public:
    static uint64_t perft(Position & pos, uint32_t depth);
    static uint64_t perftdiv(Position & pos, uint32_t depth);
};

#endif // PERFOMANCETESTER_H

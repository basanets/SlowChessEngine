#ifndef SIMPLEEVALUATOR_H
#define SIMPLEEVALUATOR_H

class Position;
#include <inttypes.h>

class SimpleEvaluator
{
public:
    static int32_t evaluate(const Position & position);
};

#endif // SIMPLEEVALUATOR_H

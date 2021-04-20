#ifndef SIMPLEEVALUATOR_H
#define SIMPLEEVALUATOR_H

class Position;
#include <inttypes.h>
#include "../BoardRepresentation/Piece.h"
#include "../BoardRepresentation/Square.h"

// https://www.chessprogramming.org/Simplified_Evaluation_Function
class SimpleEvaluator
{
public:
    // color independent eval. negative means good for black, positive - good for white
    static int32_t evaluate(const Position & position);

    // color dependent eval. Positive means good for side (param)
    static int32_t evaluate(const Position & position, Color side);
};

#endif // SIMPLEEVALUATOR_H

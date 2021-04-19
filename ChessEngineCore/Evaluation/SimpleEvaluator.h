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
   static int32_t evaluate(const Position & position);
};

#endif // SIMPLEEVALUATOR_H

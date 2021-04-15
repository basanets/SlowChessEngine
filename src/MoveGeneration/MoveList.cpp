//
// Created by mikhail on 15.04.21.
//

#include "MoveList.h"
#include "../BoardRepresentation/Position.h"
#include "MoveGenerator.h"

MoveList::MoveList(Position &position)
    : last(moveList)
{
    MoveGenerator::generateLegalMoves(*this, position);
}


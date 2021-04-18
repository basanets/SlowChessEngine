//
// Created by mikhail on 10.04.21.
//

#ifndef CHESSENGINE_DIRECTION_H
#define CHESSENGINE_DIRECTION_H

enum Direction: int
{
    NORTH_WEST =  7, NORTH           =  8, NORTH_EAST =  9,
    WEST       = -1, NULL_DIRECTION  =  0, EAST       =  1,
    SOUTH_WEST = -9, SOUTH           = -8, SOUTH_EAST = -7
};

constexpr Direction relativeDirection(Color color, Direction dir)
{
    return static_cast<Direction>(color == WHITE ? dir : -dir);
}


#endif //CHESSENGINE_DIRECTION_H

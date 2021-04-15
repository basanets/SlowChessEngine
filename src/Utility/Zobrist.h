//
// Created by mikhail on 10.04.21.
//

#ifndef CHESSENGINE_ZOBRIST_H
#define CHESSENGINE_ZOBRIST_H


#include <cstdint>
#include "../BoardRepresentation/Piece.h"
#include "../BoardRepresentation/Square.h"

class Zobrist
{
public:
    static void initializeTable();
    static uint64_t table[NUMBER_OF_PIECES][NUMBER_OF_SQUARES];
};


#endif //CHESSENGINE_ZOBRIST_H

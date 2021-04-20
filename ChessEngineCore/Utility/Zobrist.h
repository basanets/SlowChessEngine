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
    // used to hash pieces
    static uint64_t pieceTable[NUMBER_OF_PIECES][NUMBER_OF_SQUARES];

    // used to hash EP square
    static uint64_t fileTable[8];

    // to hash castling rights
    static uint64_t castlingRightsTable[4];

    static uint64_t sideToMove;
};


#endif //CHESSENGINE_ZOBRIST_H

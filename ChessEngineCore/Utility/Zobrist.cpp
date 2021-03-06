//
// Created by mikhail on 10.04.21.
//

#include "Zobrist.h"
#include <random>

uint64_t Zobrist::pieceTable[NUMBER_OF_PIECES][NUMBER_OF_SQUARES];
// used to hash EP square
uint64_t Zobrist::fileTable[8];

// to hash castling rights
uint64_t Zobrist::castlingRightsTable[4];

uint64_t Zobrist::sideToMove;


void Zobrist::initializeTable()
{
    std::mt19937 prng(0);
    std::uniform_int_distribution<uint64_t> distribution;
    for (int i = 0; i < static_cast<int>(NUMBER_OF_PIECES); ++i)
    {
        for (int j = 0; j < static_cast<int>(NUMBER_OF_SQUARES); ++j)
        {
            pieceTable[i][j] = distribution(prng);
        }
    }

    for (int i = 0; i < 8; ++i)
    {
        fileTable[i] = distribution(prng);
    }

    for (int i = 0; i < 4; ++i)
    {
        castlingRightsTable[i] = distribution(prng);
    }

    sideToMove = distribution(prng);
}

//
// Created by mikhail on 10.04.21.
//

#include "Zobrist.h"
#include <random>

uint64_t Zobrist::table[NUMBER_OF_PIECES][NUMBER_OF_SQUARES];

void Zobrist::initializeTable()
{
    std::mt19937 prng(0);
    std::uniform_int_distribution<uint64_t> distribution;
    for (int i = 0; i < static_cast<int>(NUMBER_OF_PIECES); ++i)
    {
        for (int j = 0; j < static_cast<int>(NUMBER_OF_SQUARES); ++j)
        {
            table[i][j] = distribution(prng);
        }
    }
}

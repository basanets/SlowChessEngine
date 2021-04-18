//
// Created by mikhail on 11.04.21.
//

#include "Move.h"

std::string Move::toString() const
{
    return std::string(SQUARE_STRING[from()]) + std::string(SQUARE_STRING[to()]);
}

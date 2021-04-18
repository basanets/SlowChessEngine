//
// Created by mikhail on 10.04.21.
//

#ifndef CHESSENGINE_COLOR_H
#define CHESSENGINE_COLOR_H

enum Color : int // derive from int, cause this should be faster
{
    WHITE = 0,
    BLACK = 1,
    NUMBER_OF_COLORS = 2
};

constexpr Color operator~(Color c)
{
    return static_cast<Color>(c ^ BLACK);
}

#endif //CHESSENGINE_COLOR_H

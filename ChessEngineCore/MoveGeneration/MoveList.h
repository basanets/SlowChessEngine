//
// Created by mikhail on 11.04.21.
//

#ifndef CHESSENGINE_MOVELIST_H
#define CHESSENGINE_MOVELIST_H

#include "../BoardRepresentation/Move.h"
class Position;

class MoveList
{
public:
    explicit MoveList (const Position & position);

    Move * begin()
    {
        return moveList;
    }

    Move * end()
    {
        return last;
    }

    uint32_t size() const
    {
        return last - moveList;
    }

    void push_back(Move move)
    {
        *last++ = move;
    }

    void orderMoves(const Position & position);

private:
    static constexpr uint32_t MAX_MOVES = 256; // from stockfish
    Move moveList[MAX_MOVES];
    Move * last;
};


#endif //CHESSENGINE_MOVELIST_H

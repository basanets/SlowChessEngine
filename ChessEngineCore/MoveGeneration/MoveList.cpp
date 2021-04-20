//
// Created by mikhail on 15.04.21.
//

#include "MoveList.h"
#include "../BoardRepresentation/Position.h"
#include "MoveGenerator.h"

#include <vector>

MoveList::MoveList(const Position &position)
    : last(moveList)
{
    MoveGenerator::generateLegalMoves(*this, position);
}

void MoveList::orderMoves(const Position & position)
{
    std::vector<std::pair<int32_t, Move>> prioritizedMoves;

    const Color them = ~position.sideToPlay;
    const Bitboard theirPawnAttacks = Bitboard::pawnAttacks(them, position.pieceBB[makePiece(them, PAWN)]);

    for (Move move: *this)
    {
        int32_t priority = 0;

        if (move.isCapture()) priority += 10;
        if (move.isPromotion()) priority += 5;
        if (move.isCastle()) priority += 1;

        if (move.isQuiet())
        {
            // if we move a piece to a square that is attacked by enemy pawns
            if (Bitboard::square(move.to()) & theirPawnAttacks)
            {
                priority -= 2;
            }
        }

        prioritizedMoves.push_back({priority, move});
    }

    std::sort(prioritizedMoves.begin(), prioritizedMoves.end(),
    [](const std::pair<int32_t, Move> & lhs, const std::pair<int32_t, Move> & rhs)
    {
        return lhs.first > rhs.first;
    });
    last = moveList;

    for (const auto &[p, move]: prioritizedMoves)
    {
        (void) p;
        this->push_back(move);
    }
}


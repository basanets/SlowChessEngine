//
// Created by mikhail on 11.04.21.
//

#ifndef CHESSENGINE_MOVEGENERATOR_H
#define CHESSENGINE_MOVEGENERATOR_H

#include "../BoardRepresentation/Move.h"
#include "../BoardRepresentation/Bitboard.h"

class MoveList;
class Position;

class MoveGenerator
{
public:
    static void generateLegalMoves(MoveList & list, const Position & position);

private:
    static void generateKingMoves(MoveList & list, const Position & position);
    static void generatePawnMoves(MoveList & list, const Position & position, Bitboard quietMask, Bitboard captureMask, Bitboard pinned);
    static void generateKnightMoves(MoveList & list, const Position & position, Bitboard quietMask, Bitboard captureMask, Bitboard pinned);
    static void generateSlidingMoves(MoveList & list, const Position & position, Bitboard quietMask, Bitboard captureMask, Bitboard pinned);

    template<Move::Type type>
    static void generateMoves(MoveList & list, Square from, Bitboard to);
};


#endif //CHESSENGINE_MOVEGENERATOR_H

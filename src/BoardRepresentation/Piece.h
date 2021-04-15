//
// Created by mikhail on 10.04.21.
//

#ifndef CHESSENGINE_PIECE_H
#define CHESSENGINE_PIECE_H

#include "Color.h"
#include <string>

// To do: create a class that holds both enums
enum PieceType : int
{
    NULL_PIECE_TYPE   = 0,
    PAWN   = 1,
    KNIGHT = 2,
    BISHOP = 3,
    ROOK   = 4,
    QUEEN  = 5,
    KING   = 6,
    NUMBER_OF_PIECE_TYPES = 7
};

const std::string PIECE_CHAR = "-PNBRQK--pnbrqk-";

enum Piece : int
{
    NULL_PIECE  = 0,

    WHITE_PAWN   = 1,
    WHITE_KNIGHT = 2,
    WHITE_BISHOP = 3,
    WHITE_ROOK   = 4,
    WHITE_QUEEN  = 5,
    WHITE_KING   = 6,

    BLACK_PAWN   = 9,
    BLACK_KNIGHT = 10,
    BLACK_BISHOP = 11,
    BLACK_ROOK   = 12,
    BLACK_QUEEN  = 13,
    BLACK_KING   = 14,

    NUMBER_OF_PIECES = 16
};

constexpr Piece makePiece(Color color, PieceType pieceType)
{
    return static_cast<Piece>((color << 3) | pieceType);
}

constexpr PieceType typeOf(Piece piece)
{
    constexpr int pieceTypeMask = 0b111;
    return static_cast<PieceType>(piece & pieceTypeMask);
}

#endif //CHESSENGINE_PIECE_H

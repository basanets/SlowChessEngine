//
// Created by mikhail on 11.04.21.
//

#ifndef CHESSENGINE_BB_H
#define CHESSENGINE_BB_H

#include "Bitboard.h"
#include "Square.h"
#include "Color.h"

class BB
{
    // https://www.chessprogramming.org/Magic_Bitboards
    // https://www.chessprogramming.org/Hyperbola_Quintessence
public:
    static void initializeAll();

public:
    static constexpr Bitboard EMPTY = 0ull;
    static constexpr Bitboard FULL = ~EMPTY;

    static constexpr Bitboard RANK_1 = 0xFFull;
    static constexpr Bitboard RANK_2 = RANK_1 << NORTH;
    static constexpr Bitboard RANK_3 = RANK_2 << NORTH;
    static constexpr Bitboard RANK_4 = RANK_3 << NORTH;
    static constexpr Bitboard RANK_5 = RANK_4 << NORTH;
    static constexpr Bitboard RANK_6 = RANK_5 << NORTH;
    static constexpr Bitboard RANK_7 = RANK_6 << NORTH;
    static constexpr Bitboard RANK_8 = RANK_7 << NORTH;

    static constexpr Bitboard FILE_A = 0x0101010101010101ull;
    static constexpr Bitboard FILE_B = FILE_A << EAST;
    static constexpr Bitboard FILE_C = FILE_B << EAST;
    static constexpr Bitboard FILE_D = FILE_C << EAST;
    static constexpr Bitboard FILE_E = FILE_D << EAST;
    static constexpr Bitboard FILE_F = FILE_E << EAST;
    static constexpr Bitboard FILE_G = FILE_F << EAST;
    static constexpr Bitboard FILE_H = FILE_G << EAST;

    static constexpr Bitboard WHITE_CASTLING_00_MASK =  0x90ull;
    static constexpr Bitboard WHITE_CASTLING_000_MASK = 0x11ull;
    static constexpr Bitboard WHITE_CASTLING_MASK = WHITE_CASTLING_00_MASK | WHITE_CASTLING_000_MASK;
    static constexpr Bitboard BLACK_CASTLING_00_MASK =  0x9000000000000000ull;
    static constexpr Bitboard BLACK_CASTLING_000_MASK = 0x1100000000000000ull;
    static constexpr Bitboard BLACK_CASTLING_MASK = BLACK_CASTLING_00_MASK | BLACK_CASTLING_000_MASK;
    static constexpr Bitboard ALL_CASTLING_MASK = WHITE_CASTLING_MASK | BLACK_CASTLING_MASK;

    static constexpr Bitboard WHITE_00_BLOCKERS_MASK = 0x70ull;
    static constexpr Bitboard WHITE_000_BLOCKERS_MASK = 0x1Cull;
    static constexpr Bitboard BLACK_00_BLOCKERS_MASK = 0x7000000000000000ull;
    static constexpr Bitboard BLACK_000_BLOCKERS_MASK = 0x1C00000000000000ull;

public:
    static Bitboard SQUARES[NUMBER_OF_SQUARES];
    static Bitboard RANKS[8];
    static Bitboard FILES[8];
    static Bitboard DIAGONALS[15];
    static Bitboard ANTI_DIAGONALS[15];

    static Bitboard SQUARES_BETWEEN[NUMBER_OF_SQUARES][NUMBER_OF_SQUARES];
    static Bitboard LINE[NUMBER_OF_SQUARES][NUMBER_OF_SQUARES];

public:
    static Bitboard PAWN_ATTACKS[NUMBER_OF_COLORS][NUMBER_OF_SQUARES];

    static Bitboard KING_ATTACKS[NUMBER_OF_SQUARES];
    static Bitboard KNIGHT_ATTACKS[NUMBER_OF_SQUARES];

    static Bitboard BISHOP_ATTACKS[NUMBER_OF_SQUARES][512];
    static Bitboard BISHOP_ATTACK_MASKS[NUMBER_OF_SQUARES];
    static int BISHOP_ATTACK_SHIFTS[NUMBER_OF_SQUARES];
    static Bitboard BISHOP_MAGICS[NUMBER_OF_SQUARES];
    // is 2^9. Bishop can attack at most 13 squares, 9 if excluding borders

    static Bitboard ROOK_ATTACKS[NUMBER_OF_SQUARES][4096];
    static Bitboard ROOK_ATTACK_MASKS[NUMBER_OF_SQUARES];
    static int ROOK_ATTACK_SHIFTS[NUMBER_OF_SQUARES];
    static Bitboard ROOK_MAGICS[NUMBER_OF_SQUARES];


};


#endif //CHESSENGINE_BB_H

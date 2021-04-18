//
// Created by mikhail on 10.04.21.
//

#include "Bitboard.h"
#include "BB.h"
#include <ostream>

Bitboard Bitboard::square(Square square)
{
    return BB::SQUARES[square];
}

Bitboard Bitboard::pawnAttacksTo(Color color, Square square)
{
    return BB::PAWN_ATTACKS[color][square];
}

Bitboard Bitboard::pawnAttacks(Color color, Bitboard pawns)
{
    if (color == WHITE)
    {
        return pawns.shifted(NORTH_WEST) | pawns.shifted(NORTH_EAST);
    }
    else
    {
        return pawns.shifted(SOUTH_WEST) | pawns.shifted(SOUTH_EAST);
    }
}

Bitboard Bitboard::shifted(Direction dir) const
{
    if (dir == NORTH)       return bitboard << 8;
    if (dir == SOUTH)       return bitboard >> 8;
    if (dir == EAST)        return (bitboard & ~BB::FILE_H.bitboard) << 1;
    if (dir == WEST)        return (bitboard & ~BB::FILE_A.bitboard) >> 1;
    if (dir == NORTH_EAST)  return (bitboard & ~BB::FILE_H.bitboard) << 9;
    if (dir == NORTH_WEST)  return (bitboard & ~BB::FILE_A.bitboard) << 7;
    if (dir == SOUTH_EAST)  return (bitboard & ~BB::FILE_H.bitboard) >> 7;
    if (dir == SOUTH_WEST)  return (bitboard & ~BB::FILE_A.bitboard) >> 9;
    return 0;
}

Bitboard Bitboard::kingAttacks(Square square)
{
    return BB::KING_ATTACKS[square];
}

Bitboard Bitboard::knightAttacks(Square square)
{
    return BB::KNIGHT_ATTACKS[square];
}

Bitboard Bitboard::bishopAttacks(Square square, Bitboard occupancy)
{
    const uint32_t index = ((occupancy & BB::BISHOP_ATTACK_MASKS[square]).bitboard * BB::BISHOP_MAGICS[square].bitboard) >> BB::BISHOP_ATTACK_SHIFTS[square];
    return BB::BISHOP_ATTACKS[square][index];
}

Bitboard Bitboard::rookAttacks(Square square, Bitboard occupancy)
{
    const uint32_t index = ((occupancy & BB::ROOK_ATTACK_MASKS[square]).bitboard * BB::ROOK_MAGICS[square].bitboard) >> BB::ROOK_ATTACK_SHIFTS[square];
    return BB::ROOK_ATTACKS[square][index];
}

Bitboard Bitboard::queenAttacks(Square square, Bitboard occupancy)
{
    return bishopAttacks(square, occupancy) | rookAttacks(square, occupancy);
}

Bitboard Bitboard::slidingAttacks(Square square, Bitboard occupancy, Bitboard mask)
{
    // https://www.chessprogramming.org/Hyperbola_Quintessence
    const Bitboard maskedOccupancy = occupancy & mask;
    const Bitboard firstPart = maskedOccupancy - BB::SQUARES[square] * 2;
    const Bitboard secondPart = (maskedOccupancy.reversed() - BB::SQUARES[square].reversed() * 2).reversed();
    return (firstPart ^ secondPart) & mask;
}

std::ostream &operator<<(std::ostream &os, const Bitboard &bb)
{
    for (int i = 56; i >= 0; i -= 8)
    {
        for (int j = 0; j < 8; ++j)
        {
            os << (bb.bitboard & (1ull << (i + j)) ? 1 : 0);
        }
        os << '\n';
    }
    return os;
}

Bitboard Bitboard::line(Square sq1, Square sq2)
{
    return BB::LINE[sq1][sq2];
}

Bitboard Bitboard::squaresBetween(Square sq1, Square sq2)
{
    return BB::SQUARES_BETWEEN[sq1][sq2];
}

Bitboard Bitboard::kingCastlingMask(Color color)
{
    return color == WHITE ? BB::WHITE_CASTLING_00_MASK : BB::BLACK_CASTLING_00_MASK;
}

Bitboard Bitboard::queenCastlingMask(Color color)
{
    return color == WHITE ? BB::WHITE_CASTLING_000_MASK : BB::BLACK_CASTLING_000_MASK;
}

Bitboard Bitboard::kingCastlingBlockers(Color color)
{
    return color == WHITE ? BB::WHITE_00_BLOCKERS_MASK : BB::BLACK_00_BLOCKERS_MASK;
}

Bitboard Bitboard::queenCastlingBlockers(Color color)
{
    return color == WHITE ? BB::WHITE_000_BLOCKERS_MASK : BB::BLACK_000_BLOCKERS_MASK;
}

Bitboard Bitboard::rank(Square square)
{
    return BB::RANKS[rankOf(square)];
}

Bitboard Bitboard::file(Square square)
{
    return BB::FILES[fileOf(square)];
}

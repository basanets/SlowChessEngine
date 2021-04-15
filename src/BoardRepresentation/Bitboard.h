//
// Created by mikhail on 10.04.21.
//

#ifndef CHESSENGINE_BITBOARD_H
#define CHESSENGINE_BITBOARD_H

#include <cstdint>
#include "Square.h"
#include "Color.h"
#include "Direction.h"

class Bitboard
{
public:
    constexpr Bitboard(uint64_t bitboard = 0ull)
            : bitboard(bitboard) {}
    constexpr Bitboard(const Bitboard & other) = default;
    constexpr Bitboard(Bitboard && other) = default;
    constexpr Bitboard & operator = (const Bitboard & other) = default;
    constexpr Bitboard & operator = (Bitboard && other) = default;
    constexpr ~Bitboard() = default;

public:
    constexpr Bitboard operator ~ () const
    {
        return Bitboard(~bitboard);
    }

    constexpr Bitboard operator - (const Bitboard & b) const
    {
        return Bitboard(bitboard - b.bitboard);
    }

    constexpr Bitboard operator * (const Bitboard & b) const
    {
        return Bitboard(bitboard * b.bitboard);
    }

    constexpr Bitboard operator & (const Bitboard & b) const
    {
        return Bitboard(bitboard & b.bitboard);
    }

    constexpr Bitboard & operator &= (const Bitboard & b)
    {
        this->bitboard &= b.bitboard;
        return *this;
    }

    constexpr Bitboard operator | (const Bitboard & b) const
    {
        return Bitboard(bitboard | b.bitboard);
    }

    constexpr Bitboard & operator |= (const Bitboard & b)
    {
        this->bitboard |= b.bitboard;
        return *this;
    }

    constexpr Bitboard operator ^ (const Bitboard & b) const
    {
        return Bitboard(bitboard ^ b.bitboard);
    }

    constexpr Bitboard & operator ^= (const Bitboard & b)
    {
        this->bitboard ^= b.bitboard;
        return *this;
    }

    constexpr Bitboard operator << (int shift) const
    {
        return Bitboard(bitboard << shift);
    }

    constexpr bool operator == (const Bitboard & b) const
    {
        return bitboard == b.bitboard;
    }

    constexpr bool operator != (const Bitboard & b) const
    {
        return bitboard != b.bitboard;
    }

    constexpr Bitboard reversed() const
    {
        //https://www.chessprogramming.org/Reverse_Bitboards
        uint64_t bb = bitboard;
        bb = (bb & 0x5555555555555555ull) << 1 | (bb >> 1) & 0x5555555555555555ull;
        bb = (bb & 0x3333333333333333ull) << 2 | (bb >> 2) & 0x3333333333333333ull;
        bb = (bb & 0x0f0f0f0f0f0f0f0full) << 4 | (bb >> 4) & 0x0f0f0f0f0f0f0f0full;
        bb = (bb & 0x00ff00ff00ff00ffull) << 8 | (bb >> 8) & 0x00ff00ff00ff00ffull;

        return (bb << 48) | ((bb & 0xffff0000ull) << 16) |
               ((bb >> 16) & 0xffff0000ull) | (bb >> 48);
    }

    Bitboard shifted(Direction dir) const;

    constexpr explicit operator bool() const
    {
        return static_cast<bool>(this->bitboard);
    }

    constexpr explicit operator uint64_t() const
    {
        return bitboard;
    }

    constexpr Square lsb() const
    {
        //https://www.chessprogramming.org/BitScan
        constexpr int index64[64] = {
            0,  1, 48,  2, 57, 49, 28,  3,
            61, 58, 50, 42, 38, 29, 17,  4,
            62, 55, 59, 36, 53, 51, 43, 22,
            45, 39, 33, 30, 24, 18, 12,  5,
            63, 47, 56, 27, 60, 41, 37, 16,
            54, 35, 52, 21, 44, 32, 23, 11,
            46, 26, 40, 15, 34, 20, 31, 10,
            25, 14, 19,  9, 13,  8,  7,  6
        };

        constexpr uint64_t debruijn64 = 0x03f79d71b4cb0a89;
        return static_cast<Square>(index64[((bitboard & -bitboard) * debruijn64) >> 58]);
    }

    constexpr Square popLsb()
    {
        Square lsb = this->lsb();
        bitboard &= (bitboard - 1);
        return lsb;
    }

    constexpr int populationCount() const
    {
        // https://www.chessprogramming.org/Population_Count
        constexpr Bitboard K1 = 0x5555555555555555ull;
        constexpr Bitboard K2 = 0x3333333333333333ull;
        constexpr Bitboard K4 = 0x0f0f0f0f0f0f0f0full;
        constexpr Bitboard KF = 0x0101010101010101ull;

        uint64_t x = bitboard;
        x = x - ((x >> 1) & K1.bitboard);
        x = (x & K2.bitboard) + ((x >> 2) & K2.bitboard);
        x = (x + (x >> 4)) & K4.bitboard;
        x = (x * KF.bitboard) >> 56;
        return static_cast<int>(x);
    }

    friend std::ostream & operator << (std::ostream & os, const Bitboard & bb);

public:
    static Bitboard square(Square square);

    static Bitboard kingCastlingMask(Color color);
    static Bitboard queenCastlingMask(Color color);
    static Bitboard kingCastlingBlockers(Color color);
    static Bitboard queenCastlingBlockers(Color color);
    static Bitboard slidingAttacks(Square square, Bitboard occupancy, Bitboard mask);

    static Bitboard pawnAttacksTo(Color color, Square square);
    static Bitboard pawnAttacks(Color color, Bitboard pawns);
    static Bitboard kingAttacks(Square square);
    static Bitboard knightAttacks(Square square);
    static Bitboard bishopAttacks(Square square, Bitboard occupancy);
    static Bitboard rookAttacks(Square square, Bitboard occupancy);
    static Bitboard queenAttacks(Square square, Bitboard occupancy);
    static Bitboard line(Square sq1, Square sq2);
    static Bitboard squaresBetween(Square sq1, Square sq2);
    static Bitboard rank(Square sq);
    static Bitboard file(Square sq);
private:
    uint64_t bitboard;
};

//const

#endif //CHESSENGINE_BITBOARD_H

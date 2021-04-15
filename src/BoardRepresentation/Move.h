//
// Created by mikhail on 11.04.21.
//

#ifndef CHESSENGINE_MOVE_H
#define CHESSENGINE_MOVE_H

#include <cstdint>
#include "Square.h"

class Move
{
public:
    enum Type: int
    {
        QUIET ,
        CAPTURE,
        DOUBLE_PUSH ,
        CASTLE_00,
        CASTLE_000,
        EN_PASSANT,

        PROMOTION,
        PROMOTION_KNIGHT,
        PROMOTION_BISHOP,
        PROMOTION_ROOK,
        PROMOTION_QUEEN,

        PROMOTION_CAPTURE,
        PROMOTION_CAPTURE_KNIGHT,
        PROMOTION_CAPTURE_BISHOP,
        PROMOTION_CAPTURE_ROOK,
        PROMOTION_CAPTURE_QUEEN
    };

private:
    uint16_t move;

public:
    constexpr explicit Move()
            : move(0) {}

    constexpr Move(Square from, Square to, Type type = Type::QUIET)
            : move((type << 12) | (from << 6) | to) {}

    constexpr Move(const Move & other) = default;
    constexpr Move(Move && other) = default;
    constexpr Move & operator = (const Move & other) = default;
    constexpr Move & operator = (Move && other) = default;

    constexpr ~Move() = default;

public:

    constexpr Square to() const
    {
        return static_cast<Square>(move & 0b111111);
    }

    constexpr Square from() const
    {
        return static_cast<Square>((move >> 6) & 0b111111);
    }

    constexpr Type type() const
    {
        return static_cast<Type>(move >> 12);
    }

    std::string toString() const;
};


#endif //CHESSENGINE_MOVE_H

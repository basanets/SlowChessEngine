#include "SimpleEvaluator.h"

#include <array>

#include <BoardRepresentation/Position.h>

static constexpr std::array<int32_t, NUMBER_OF_PIECE_TYPES> PIECE_VALUES =
{
    0,  // null piece
    100, // pawn
    300, // knight
    300, // bishop
    500, // rook
    900, // queen
    0, // king is unvaluable
};

// location bonuses for pieces
static constexpr std::array<std::array<int32_t, NUMBER_OF_SQUARES>, NUMBER_OF_PIECE_TYPES> SQUARE_VALUES =
{
    {
        // null piece
        {
            0,  0,  0,  0,  0,  0,  0,  0,
            50, 50, 50, 50, 50, 50, 50, 50,
            10, 10, 20, 30, 30, 20, 10, 10,
             5,  5, 10, 25, 25, 10,  5,  5,
             0,  0,  0, 20, 20,  0,  0,  0,
             5, -5,-10,  0,  0,-10, -5,  5,
             5, 10, 10,-20,-20, 10, 10,  5,
             0,  0,  0,  0,  0,  0,  0,  0,
        },

        // pawns
        {
            0,  0,  0,  0,  0,  0,  0,  0,
           50, 50, 50, 50, 50, 50, 50, 50,
           10, 10, 20, 30, 30, 20, 10, 10,
            5,  5, 10, 25, 25, 10,  5,  5,
            0,  0,  0, 20, 20,  0,  0,  0,
            5, -5,-10,  0,  0,-10, -5,  5,
            5, 10, 10,-20,-20, 10, 10,  5,
            0,  0,  0,  0,  0,  0,  0,  0,
        },

        // knights
        {
            -50,-40,-30,-30,-30,-30,-40,-50,
            -40,-20,  0,  0,  0,  0,-20,-40,
            -30,  0, 10, 15, 15, 10,  0,-30,
            -30,  5, 15, 20, 20, 15,  5,-30,
            -30,  0, 15, 20, 20, 15,  0,-30,
            -30,  5, 10, 15, 15, 10,  5,-30,
            -40,-20,  0,  5,  5,  0,-20,-40,
            -50,-40,-30,-30,-30,-30,-40,-50,
        },

        // bishops
        {
            -20,-10,-10,-10,-10,-10,-10,-20,
            -10,  0,  0,  0,  0,  0,  0,-10,
            -10,  0,  5, 10, 10,  5,  0,-10,
            -10,  5,  5, 10, 10,  5,  5,-10,
            -10,  0, 10, 10, 10, 10,  0,-10,
            -10, 10, 10, 10, 10, 10, 10,-10,
            -10,  5,  0,  0,  0,  0,  5,-10,
            -20,-10,-10,-10,-10,-10,-10,-20,
        },

        // rooks
        {
            0,  0,  0,  0,  0,  0,  0,  0,
            5, 10, 10, 10, 10, 10, 10,  5,
           -5,  0,  0,  0,  0,  0,  0, -5,
           -5,  0,  0,  0,  0,  0,  0, -5,
           -5,  0,  0,  0,  0,  0,  0, -5,
           -5,  0,  0,  0,  0,  0,  0, -5,
           -5,  0,  0,  0,  0,  0,  0, -5,
            0,  0,  0,  5,  5,  0,  0,  0,
        },

        // queens
        {
            -20,-10,-10, -5, -5,-10,-10,-20,
            -10,  0,  0,  0,  0,  0,  0,-10,
            -10,  0,  5,  5,  5,  5,  0,-10,
             -5,  0,  5,  5,  5,  5,  0, -5,
              0,  0,  5,  5,  5,  5,  0, -5,
            -10,  5,  5,  5,  5,  5,  0,-10,
            -10,  0,  5,  0,  0,  0,  0,-10,
            -20,-10,-10, -5, -5,-10,-10,-20,
        },

        // king
        {
            -30,-40,-40,-50,-50,-40,-40,-30,
            -30,-40,-40,-50,-50,-40,-40,-30,
            -30,-40,-40,-50,-50,-40,-40,-30,
            -30,-40,-40,-50,-50,-40,-40,-30,
            -20,-30,-30,-40,-40,-30,-30,-20,
            -10,-20,-20,-20,-20,-20,-20,-10,
             20, 20,  0,  0,  0,  0, 20, 20,
             20, 30, 10,  0,  0, 10, 30, 20,
        }
    }
};


static constexpr auto generatePieceSquareValues()
{
    std::array<std::array<std::array<int32_t, NUMBER_OF_SQUARES>, NUMBER_OF_PIECE_TYPES>, NUMBER_OF_COLORS> result = {};

    for (PieceType pieceType = PieceType::PAWN; pieceType < PieceType::NUMBER_OF_PIECE_TYPES; pieceType = static_cast<PieceType>(pieceType + 1))
    {
        for (Square square = A1; square < NUMBER_OF_SQUARES; ++square)
        {
            result[WHITE][pieceType][square] = PIECE_VALUES[pieceType] + SQUARE_VALUES[pieceType][square];
            result[BLACK][pieceType][square] = -(PIECE_VALUES[pieceType] + SQUARE_VALUES[pieceType][mirrored(square)]);
        }
    }

    return result;
}

static constexpr std::array<std::array<std::array<int32_t, NUMBER_OF_SQUARES>, NUMBER_OF_PIECE_TYPES>, NUMBER_OF_COLORS> PIECE_SQUARE_VALUES = generatePieceSquareValues();
//static constexpr int32_t PIECE_SQUARE_VALUES[NUMBER_OF_COLORS][NUMBER_OF_PIECE_TYPES][NUMBER_OF_SQUARES]


int32_t SimpleEvaluator::evaluate(const Position & position)
{
    int32_t evaluation = 0;

    for (Square sq = A1; sq < NUMBER_OF_SQUARES; ++sq)
    {
        if (position.mailbox[sq] != NULL_PIECE)
        {
            const Piece piece = position.mailbox[sq];
            evaluation += PIECE_SQUARE_VALUES[colorOf(piece)][typeOf(piece)][sq];
        }
    }

    return evaluation;
}

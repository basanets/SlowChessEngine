//
// Created by mikhail on 10.04.21.
//

#ifndef CHESSENGINE_POSITION_H
#define CHESSENGINE_POSITION_H


#include <string>
#include "Bitboard.h"
#include "Piece.h"
#include "Square.h"
#include "Move.h"
#include "Direction.h"
#include "../Utility/FenUtility.h"

class Position
{
public:
    struct UnrecoverableState
    {
        constexpr UnrecoverableState()
            : movedPieces(0ull),
            lastCaptured(NULL_PIECE),
            enPassantSquare(NULL_SQUARE),
            plyFiftyMoveRule(0)
        {}

        constexpr UnrecoverableState(const UnrecoverableState & other)
            : movedPieces(other.movedPieces)
            , lastCaptured(NULL_PIECE)
            , enPassantSquare(NULL_SQUARE)
            , plyFiftyMoveRule(other.plyFiftyMoveRule + 1)
        {}


        Bitboard movedPieces;
        Piece lastCaptured;
        Square enPassantSquare;
        int plyFiftyMoveRule;
    };

public:
    UnrecoverableState history[256];
    Bitboard pieceBB[NUMBER_OF_PIECES];

    Piece mailbox[NUMBER_OF_SQUARES];

    uint64_t hash;
    uint32_t gamePly;
    Color sideToPlay;

public:
    explicit Position(const std::string & fen = FenUtility::DEFAULT_FEN);
    Position(const Position & pos) = delete;
    Position(Position && pos) = delete;
    Position & operator = (const Position & pos) = delete;
    Position & operator = (Position && pos) = delete;
    ~Position() = default;

public:
    void set(const std::string & fen);
    std::string fen() const;

    void putPiece(Piece piece, Square to);
    void removePiece(Square from);

    void movePieceQuiet(Square from, Square to);

    void makeMove(Move move);
    void undoMove(Move move);

    Bitboard getPieces(Color color) const;
    Bitboard getDiagonalSliders(Color color) const;
    Bitboard getOrthogonalSliders(Color color) const;
    Bitboard getCheckers() const;
    Bitboard getPinnedPieces() const;

    friend std::ostream & operator << (std::ostream & os, const Position & pos);
};

#endif //CHESSENGINE_POSITION_H

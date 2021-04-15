//
// Created by mikhail on 10.04.21.
//

#include "Position.h"
#include "../Utility/Zobrist.h"
#include "../Utility/FenUtility.h"
#include <ostream>

Position::Position(const std::string &fen)
{
    std::fill(mailbox, mailbox + NUMBER_OF_SQUARES, NULL_PIECE);
    std::fill(pieceBB, pieceBB + NUMBER_OF_PIECES, Bitboard());
    std::fill(history, history + 256, UnrecoverableState());
    hash = 0;
    gamePly = 0;
    sideToPlay = WHITE;

    set(fen);
}

void Position::set(const std::string &fen)
{
    FenUtility::set(*this, fen);
}

std::string Position::fen() const
{
    return FenUtility::fen(*this);
}

void Position::putPiece(Piece piece, Square to)
{
    hash ^= Zobrist::table[piece][to];
    pieceBB[piece] |= Bitboard::square(to);
    mailbox[to] = piece;
}

void Position::removePiece(Square from)
{
    hash ^= Zobrist::table[mailbox[from]][from];
    pieceBB[mailbox[from]] &= ~Bitboard::square(from);
    mailbox[from] = NULL_PIECE;
}

void Position::movePieceQuiet(Square from, Square to)
{
    putPiece(mailbox[from], to);
    removePiece(from);
}

std::ostream &operator<<(std::ostream &os, const Position &pos)
{
    const char* s = "   +---+---+---+---+---+---+---+---+\n";
    const char* t = "     A   B   C   D   E   F   G   H\n";
    os << t;
    for (int i = 56; i >= 0; i -= 8)
    {
        os << s << " " << i / 8 + 1 << " ";
        for (int j = 0; j < 8; ++j)
        {
            os << "| " << PIECE_CHAR[pos.mailbox[i + j]] << " ";
        }
        os << "| " << i / 8 + 1 << "\n";
    }
    os << s;
    os << t << "\n";

    os << "FEN: " << pos.fen() << "\n";
    os << "Hash: 0x" << std::hex << pos.hash << std::dec << "\n";

    return os;
}

void Position::makeMove(Move move)
{
    const Color us = sideToPlay;

    sideToPlay = ~sideToPlay;
    ++gamePly;

    const Square from = move.from();
    const Square to = move.to();
    history[gamePly] = UnrecoverableState(history[gamePly - 1]);
    history[gamePly].movedPieces |= (Bitboard::square(to) | Bitboard::square(from));

    if (typeOf(mailbox[from]) == PAWN)
    {
        history[gamePly].plyFiftyMoveRule = 0;
    }

    switch (move.type())
    {
        case Move::QUIET:
            movePieceQuiet(from, to);
            break;

        case Move::CAPTURE:
            history[gamePly].plyFiftyMoveRule = 0;
            history[gamePly].lastCaptured = mailbox[to];
            removePiece(to);
            putPiece(mailbox[from], to);
            removePiece(from);
            break;

        case Move::DOUBLE_PUSH:
            movePieceQuiet(from, to);
            history[gamePly].enPassantSquare = static_cast<Square>(to + relativeDirection(us, SOUTH));
            break;

        case Move::CASTLE_00:
            if (us == WHITE)
            {
                movePieceQuiet(E1, G1);
                movePieceQuiet(H1, F1);
            }
            else
            {
                movePieceQuiet(E8, G8);
                movePieceQuiet(H8, F8);
            }
            break;

        case Move::CASTLE_000:
            if (us == WHITE)
            {
                movePieceQuiet(E1, C1);
                movePieceQuiet(A1, D1);
            }
            else
            {
                movePieceQuiet(E8, C8);
                movePieceQuiet(A8, D8);
            }
            break;

        case Move::EN_PASSANT:
            movePieceQuiet(from, to);
            history[gamePly].lastCaptured = mailbox[static_cast<Square>(to + relativeDirection(us, SOUTH))];
            removePiece(static_cast<Square>(to + relativeDirection(us, SOUTH)));
            break;

        case Move::PROMOTION_KNIGHT:
            removePiece(from);
            putPiece(makePiece(us, KNIGHT), to);
            break;

        case Move::PROMOTION_BISHOP:
            removePiece(from);
            putPiece(makePiece(us, BISHOP), to);
            break;

        case Move::PROMOTION_ROOK:
            removePiece(from);
            putPiece(makePiece(us, ROOK), to);
            break;

        case Move::PROMOTION_QUEEN:
            removePiece(from);
            putPiece(makePiece(us, QUEEN), to);
            break;

        case Move::PROMOTION_CAPTURE_KNIGHT:
            history[gamePly].plyFiftyMoveRule = 0;
            history[gamePly].lastCaptured = mailbox[to];
            removePiece(from);
            removePiece(to);
            putPiece(makePiece(us, KNIGHT), to);
            break;

        case Move::PROMOTION_CAPTURE_BISHOP:
            history[gamePly].plyFiftyMoveRule = 0;
            history[gamePly].lastCaptured = mailbox[to];
            removePiece(from);
            removePiece(to);
            putPiece(makePiece(us, BISHOP), to);
            break;

        case Move::PROMOTION_CAPTURE_ROOK:
            history[gamePly].plyFiftyMoveRule = 0;
            history[gamePly].lastCaptured = mailbox[to];
            removePiece(from);
            removePiece(to);
            putPiece(makePiece(us, ROOK), to);
            break;

        case Move::PROMOTION_CAPTURE_QUEEN:
            history[gamePly].plyFiftyMoveRule = 0;
            history[gamePly].lastCaptured = mailbox[to];
            removePiece(from);
            removePiece(to);
            putPiece(makePiece(us, QUEEN), to);
            break;
    }
}

void Position::undoMove(Move move)
{
    const Color us = ~sideToPlay; // we moved before, we undo
    const Square from = move.from();
    const Square to = move.to();

    switch (move.type())
    {
        case Move::QUIET:
        case Move::DOUBLE_PUSH:
            movePieceQuiet(to, from);
            break;

        case Move::CAPTURE:
            movePieceQuiet(to, from);
            putPiece(history[gamePly].lastCaptured, to);
            break;

        case Move::CASTLE_00:
            if (us == WHITE)
            {
                movePieceQuiet(G1, E1);
                movePieceQuiet(F1, H1);
            }
            else
            {
                movePieceQuiet(G8, E8);
                movePieceQuiet(F8, H8);
            }
            break;

        case Move::CASTLE_000:
            if (us == WHITE)
            {
                movePieceQuiet(C1, E1);
                movePieceQuiet(D1, A1);
            }
            else
            {
                movePieceQuiet(C8, E8);
                movePieceQuiet(D8, A8);
            }
            break;

        case Move::EN_PASSANT:
            movePieceQuiet(to, from);
            putPiece(makePiece(~us, PAWN), static_cast<Square>(to + relativeDirection(us, SOUTH)));
            break;

        case Move::PROMOTION_KNIGHT:
        case Move::PROMOTION_BISHOP:
        case Move::PROMOTION_ROOK:
        case Move::PROMOTION_QUEEN:
            removePiece(to);
            putPiece(makePiece(us, PAWN), from);
            break;

        case Move::PROMOTION_CAPTURE_KNIGHT:
        case Move::PROMOTION_CAPTURE_BISHOP:
        case Move::PROMOTION_CAPTURE_ROOK:
        case Move::PROMOTION_CAPTURE_QUEEN:
            removePiece(to);
            putPiece(makePiece(us, PAWN), from);
            putPiece(history[gamePly].lastCaptured, to);
            break;
    }

    sideToPlay = ~sideToPlay;
    --gamePly;
}

Bitboard Position::getPieces(Color color) const
{
    // need to make template and constexpr
    return pieceBB[makePiece(color, PAWN)]
         | pieceBB[makePiece(color, KNIGHT)]
         | pieceBB[makePiece(color, BISHOP)]
         | pieceBB[makePiece(color, ROOK)]
         | pieceBB[makePiece(color, QUEEN)]
         | pieceBB[makePiece(color, KING)];
}

Bitboard Position::getDiagonalSliders(Color color) const
{
    // need to make template and constexpr
    return pieceBB[makePiece(color, BISHOP)]
         | pieceBB[makePiece(color, QUEEN)];
}

Bitboard Position::getOrthogonalSliders(Color color) const
{
    // need to make template and constexpr
    return pieceBB[makePiece(color, ROOK)]
         | pieceBB[makePiece(color, QUEEN)];
}

Bitboard Position::getCheckers() const
{
    const Color us = sideToPlay;
    const Color them = ~us;
    const Bitboard bbUs = getPieces(us);
    const Bitboard bbThem = getPieces(them);

    const Square ourKing = pieceBB[makePiece(us, KING)].lsb();

    Bitboard checkers = 0;
    checkers |= Bitboard::knightAttacks(ourKing) & pieceBB[makePiece(them, KNIGHT)];
    checkers |= Bitboard::pawnAttacksTo(us, ourKing) & pieceBB[makePiece(them, PAWN)];

    Bitboard xRaySliders = 0;
    xRaySliders |= Bitboard::rookAttacks(ourKing, bbThem) & getOrthogonalSliders(them);
    xRaySliders |= Bitboard::bishopAttacks(ourKing, bbThem) & getDiagonalSliders(them);

    while (xRaySliders)
    {
        Square slider = xRaySliders.popLsb();
        Bitboard ourPiecesBetween = Bitboard::squaresBetween(ourKing, slider) & bbUs;
        if (ourPiecesBetween == 0)
        {
            checkers |= Bitboard::square(slider);
        }
    }

    return checkers;
}

Bitboard Position::getPinnedPieces() const
{
    const Color us = sideToPlay;
    const Color them = ~us;
    const Bitboard bbUs = getPieces(us);
    const Bitboard bbThem = getPieces(them);
    const Square ourKing = pieceBB[makePiece(us, KING)].lsb();

    Bitboard xRaySliders = 0;
    xRaySliders |= Bitboard::rookAttacks(ourKing, bbThem) & getOrthogonalSliders(them);
    xRaySliders |= Bitboard::bishopAttacks(ourKing, bbThem) & getDiagonalSliders(them);

    Bitboard pinned = 0;
    while (xRaySliders)
    {
        Square slider = xRaySliders.popLsb();
        Bitboard ourPiecesBetween = Bitboard::squaresBetween(ourKing, slider) & bbUs;
        if ((ourPiecesBetween & (ourPiecesBetween - 1)) == 0)
        {
            pinned |= ourPiecesBetween;
        }
    }

    return pinned;
}

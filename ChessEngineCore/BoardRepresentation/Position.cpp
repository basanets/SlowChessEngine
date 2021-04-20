//
// Created by mikhail on 10.04.21.
//

#include "Position.h"
#include "../Utility/Zobrist.h"
#include "../Utility/FenUtility.h"
#include <ostream>
#include "../Evaluation/SimpleEvaluator.h"
#include <MoveGeneration/MoveList.h>

Position::Position(const std::string &fen)
{
    clear();
    set(fen);
}

Position::Position(const Position & pos)
{
    std::copy(pos.mailbox, pos.mailbox + NUMBER_OF_SQUARES, mailbox);
    std::copy(pos.pieceBB, pos.pieceBB + NUMBER_OF_PIECES, pieceBB);
    std::copy(pos.colorBB, pos.colorBB + NUMBER_OF_PIECES, colorBB);
    std::copy(pos.history, pos.history + 256, history);
    hash = pos.hash;
    gamePly = pos.gamePly;
    sideToPlay = pos.sideToPlay;
}

void Position::clear()
{
    std::fill(mailbox, mailbox + NUMBER_OF_SQUARES, NULL_PIECE);
    std::fill(pieceBB, pieceBB + NUMBER_OF_PIECES, Bitboard());
    std::fill(colorBB, colorBB + NUMBER_OF_PIECES, Bitboard());
    std::fill(history, history + 256, UnrecoverableState());
    hash = 0;
    gamePly = 0;
    sideToPlay = WHITE;
}

Position::Status Position::status() const
{
    MoveList list(*this);
    if (list.size() == 0)
    {
        if (getCheckers() == 0)
            return STALEMATE;
        else
        {
            if (sideToPlay == WHITE) return BLACK_WIN;
            else                     return WHITE_WIN;
        }
    }

    // add threefold repetition by hash
    if (history[gamePly].plyFiftyMoveRule >= 50)
        return DRAW;

    return NOT_FINISHED;
}

void Position::set(const std::string &fen)
{
    FenUtility::set(*this, fen);

    if (sideToPlay == BLACK)
        hash ^= Zobrist::sideToMove;

    updateNonPieceHashing(gamePly);
    recalculateCheckersAndPinned();
}

std::string Position::fen() const
{
    return FenUtility::fen(*this);
}

Move Position::moveFromString(const std::string & move)
{
    std::string fromStr = move.substr(0, 2);
    std::string toStr = move.substr(2, 2);
    std::string promotionPiece = "";
    if (move.size() > 4)
        promotionPiece = move.substr(4);

    Square from = static_cast<Square>(std::find(SQUARE_STRING, SQUARE_STRING + NUMBER_OF_SQUARES, fromStr) - SQUARE_STRING);
    Square to = static_cast<Square>(std::find(SQUARE_STRING, SQUARE_STRING + NUMBER_OF_SQUARES, toStr) - SQUARE_STRING);
    Move::Type type = Move::Type::QUIET;

    switch (typeOf(mailbox[from])) {
    case PAWN:
        if (fileOf(from) == fileOf(to))
        {
            // non-capture
            if (std::abs(rankOf(from) - rankOf(to)) == 2) type = Move::Type::DOUBLE_PUSH;
            else if (promotionPiece == "n")  type = Move::Type::PROMOTION_KNIGHT;
            else if (promotionPiece == "b")  type = Move::Type::PROMOTION_BISHOP;
            else if (promotionPiece == "r")  type = Move::Type::PROMOTION_ROOK;
            else if (promotionPiece == "q")  type = Move::Type::PROMOTION_QUEEN;
        }
        else
        {
            // capture
            if   (mailbox[to] == NULL_PIECE) type = Move::Type::EN_PASSANT;
            else if (promotionPiece == "")   type = Move::Type::CAPTURE;
            else if (promotionPiece == "n")  type = Move::Type::PROMOTION_CAPTURE_KNIGHT;
            else if (promotionPiece == "b")  type = Move::Type::PROMOTION_CAPTURE_BISHOP;
            else if (promotionPiece == "r")  type = Move::Type::PROMOTION_CAPTURE_ROOK;
            else if (promotionPiece == "q")  type = Move::Type::PROMOTION_CAPTURE_QUEEN;
        }
        break;

    case KING:
        if (fileOf(from) == fileOf(E1) && fileOf(to) == fileOf(G1))
        {
            type = Move::Type::CASTLE_00;
        }
        else if (fileOf(from) == fileOf(E1) && fileOf(to) == fileOf(C1))
        {
            type = Move::Type::CASTLE_000;
        }
        else if (mailbox[to] != NULL_PIECE)
        {
            type = Move::Type::CAPTURE;
        }
        break;

    case KNIGHT:
    case BISHOP:
    case ROOK:
    case QUEEN:
        if (mailbox[to] != NULL_PIECE)
        {
            type = Move::Type::CAPTURE;
        }

        break;

        // to avoid warnings
    case NULL_PIECE_TYPE:
    case NUMBER_OF_PIECE_TYPES:
        break;
    }

    return Move(from, to, type);
}

void Position::putPiece(Piece piece, Square to)
{
    hash ^= Zobrist::pieceTable[piece][to];
    pieceBB[piece] |= Bitboard::square(to);
    colorBB[colorOf(piece)] |= Bitboard::square(to);

    mailbox[to] = piece;
}

void Position::removePiece(Square from)
{
    const Piece piece = mailbox[from];

    hash ^= Zobrist::pieceTable[piece][from];
    pieceBB[piece] &= ~Bitboard::square(from);
    colorBB[colorOf(piece)] &= ~Bitboard::square(from);

    mailbox[from] = NULL_PIECE;
}

void Position::movePieceQuiet(Square from, Square to)
{
    putPiece(mailbox[from], to);
    removePiece(from);
}

// parameter for make-unmake
void Position::updateNonPieceHashing(int updateGamePly)
{
    hash ^= Zobrist::castlingRightsTable[Bitboard::castleRightsFromMovedPieces(history[updateGamePly].movedPieces)];

    if (history[updateGamePly].enPassantSquare != NULL_SQUARE)
        hash ^= Zobrist::fileTable[fileOf(history[updateGamePly].enPassantSquare)];
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

    hash ^= Zobrist::sideToMove;
    updateNonPieceHashing(gamePly);
    // still positive cause we made a move
    updateNonPieceHashing(gamePly - 1);
    recalculateCheckersAndPinned();
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

    hash ^= Zobrist::sideToMove;
    updateNonPieceHashing(gamePly);
    // still positive cause couldn't have made an undo otherwise
    updateNonPieceHashing(gamePly - 1);

    sideToPlay = ~sideToPlay;
    --gamePly;
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

void Position::recalculateCheckersAndPinned()
{
    const Color us = sideToPlay;
    const Color them = ~us;
    const Bitboard bbUs = colorBB[us];
    const Bitboard bbThem = colorBB[them];

    const Square ourKing = pieceBB[makePiece(us, KING)].lsb();

    Bitboard pinned = 0;
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
        else if ((ourPiecesBetween & (ourPiecesBetween - 1)) == 0)
        {
            pinned |= ourPiecesBetween;
        }
    }

    history[gamePly].checkers = checkers;
    history[gamePly].pinned = pinned;
}

Bitboard Position::getCheckers() const
{
    return history[gamePly].checkers;
}

Bitboard Position::getPinnedPieces() const
{
    return history[gamePly].pinned;
}

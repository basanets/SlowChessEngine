//
// Created by mikhail on 11.04.21.
//

#include <cassert>
#include "MoveGenerator.h"
#include "../BoardRepresentation/Position.h"
#include "MoveList.h"

void MoveGenerator::generateLegalMoves(MoveList &list, const Position &position)
{
    const Color us = position.sideToPlay;
    const Color them = ~us;

    const Bitboard bbUs = position.getPieces(us);
    const Bitboard bbThem = position.getPieces(them);
    const Bitboard bbAll = bbUs | bbThem;

    const Bitboard checkers = position.getCheckers();
    const Bitboard pinned = position.getPinnedPieces();

    Bitboard captureMask = bbThem;
    Bitboard quietMask = ~bbAll;

    generateKingMoves(list, position);
    int numberOfCheckers = checkers.populationCount();
    if (numberOfCheckers == 2)
    {
        return; // only king moves
    }
    else if (numberOfCheckers == 1)
    {
        captureMask = checkers;

        Square checker = checkers.lsb();

        if (position.mailbox[checker] == makePiece(them, PAWN) ||
            position.mailbox[checker] == makePiece(them, KNIGHT))
        {
            quietMask = 0;
        }
        else
        {
            Square ourKing = position.pieceBB[makePiece(us, KING)].lsb();
            quietMask = Bitboard::squaresBetween(ourKing, checker);
        }
    }
    generateSlidingMoves(list, position, quietMask, captureMask, pinned);
    generateKnightMoves(list, position, quietMask, captureMask, pinned);
    generatePawnMoves(list, position, quietMask, captureMask, pinned);
}

template<Move::Type type>
void MoveGenerator::generateMoves(MoveList &list, Square from, Bitboard to)
{
    while (to)
    {
        if constexpr (type == Move::PROMOTION)
        {
            Square sq = to.popLsb();
            list.push_back(Move(from, sq, Move::PROMOTION_QUEEN));
            list.push_back(Move(from, sq, Move::PROMOTION_KNIGHT));
            list.push_back(Move(from, sq, Move::PROMOTION_BISHOP));
            list.push_back(Move(from, sq, Move::PROMOTION_ROOK));
        }
        else if constexpr (type == Move::PROMOTION_CAPTURE)
        {
            Square sq = to.popLsb();
            list.push_back(Move(from, sq, Move::PROMOTION_CAPTURE_QUEEN));
            list.push_back(Move(from, sq, Move::PROMOTION_CAPTURE_KNIGHT));
            list.push_back(Move(from, sq, Move::PROMOTION_CAPTURE_BISHOP));
            list.push_back(Move(from, sq, Move::PROMOTION_CAPTURE_ROOK));
        }
        else
        {
            list.push_back(Move(from, to.popLsb(), type));
        }
    }
}

void MoveGenerator::generateKingMoves(MoveList &list, const Position &position)
{
    const Color us = position.sideToPlay;
    const Color them = ~us;

    const Bitboard bbUs = position.getPieces(us);
    const Bitboard bbThem = position.getPieces(them);
    const Bitboard bbAll = bbUs | bbThem;

    const Square ourKing = position.pieceBB[makePiece(us, KING)].lsb();
    const Square theirKing = position.pieceBB[makePiece(them, KING)].lsb();

    // squares attacked by enemy pieces
    Bitboard attackedSquares = 0ull;
    attackedSquares |= Bitboard::pawnAttacks(them, position.pieceBB[makePiece(them, PAWN)]);
    attackedSquares |= Bitboard::kingAttacks(theirKing);
    Bitboard theirKnights = position.pieceBB[makePiece(them, KNIGHT)];
    while (theirKnights) attackedSquares |= Bitboard::knightAttacks(theirKnights.popLsb());
    // exclude the king to prevent it from moving behind itself (which still will be attacked)
    Bitboard theirDiagSliders = position.getDiagonalSliders(them);
    while (theirDiagSliders) attackedSquares |= Bitboard::bishopAttacks(theirDiagSliders.popLsb(), bbAll ^ Bitboard::square(ourKing));
    Bitboard theirOrthogonalSliders = position.getOrthogonalSliders(them);
    while (theirOrthogonalSliders) attackedSquares |= Bitboard::rookAttacks(theirOrthogonalSliders.popLsb(), bbAll ^ Bitboard::square(ourKing));

    Bitboard kingMoves = Bitboard::kingAttacks(ourKing) & ~(bbUs | attackedSquares); // we cannot move to attacked squares and our squares;
    generateMoves<Move::Type::QUIET>(list, ourKing, kingMoves & (~bbThem));
    generateMoves<Move::Type::CAPTURE>(list, ourKing, kingMoves & bbThem);

    // generate castling
    const Bitboard movedPieces = position.history[position.gamePly].movedPieces;

    if ( !(movedPieces & Bitboard::kingCastlingMask(us)) &&
         !(((bbAll & (~Bitboard::square(ourKing))) | attackedSquares) & Bitboard::kingCastlingBlockers(us)))
    {
        if (us == WHITE)  list.push_back(Move(E1, G1, Move::CASTLE_00));
        else              list.push_back(Move(E8, G8, Move::CASTLE_00));
    }

    if ( !(movedPieces & Bitboard::queenCastlingMask(us)) &&
         !(attackedSquares & Bitboard::queenCastlingBlockers(us)) &&
         !(bbAll & Bitboard::squaresBetween(ourKing, us == WHITE ? A1 : A8)))
    {
        if (us == WHITE) list.push_back(Move(E1, C1, Move::CASTLE_000));
        else             list.push_back(Move(E8, C8, Move::CASTLE_000));
    }
}

void MoveGenerator::generatePawnMoves(MoveList &list, const Position &position, Bitboard quietMask, Bitboard captureMask, Bitboard pinned)
{
    const Color us = position.sideToPlay;
    const Color them = ~us;
    const Square ourKing = position.pieceBB[makePiece(us, KING)].lsb();

    const Bitboard relativeRank2 = (us == WHITE ? Bitboard::rank(A2) : Bitboard::rank(A7));
    const Bitboard relativeRank4 = (us == WHITE ? Bitboard::rank(A4) : Bitboard::rank(A5));
    const Bitboard relativeRank7 = (us == WHITE ? Bitboard::rank(A7) : Bitboard::rank(A2));

    const Bitboard bbUs = position.getPieces(us);
    const Bitboard bbThem = position.getPieces(them);
    const Bitboard bbAll = bbUs | bbThem;

    const Bitboard ourPawns = position.pieceBB[makePiece(us, PAWN)];
    const Bitboard pinnedPawns = ourPawns & pinned;
    const Bitboard nonPinnedPawns = ourPawns & (~pinned);

    // check en-passant moves first
    const Square enPassantSq = position.history[position.gamePly].enPassantSquare;
    if ((enPassantSq != NULL_SQUARE) &&
        (captureMask & Bitboard::square(enPassantSq).shifted(relativeDirection(them, NORTH))))
    {
        const Bitboard theirOrthogonalSliders = position.getOrthogonalSliders(them);

        Bitboard nonPinnedCandidate = Bitboard::pawnAttacksTo(them, enPassantSq) & nonPinnedPawns;
        while (nonPinnedCandidate)
        {
            Square square = nonPinnedCandidate.popLsb();

            Bitboard occupancyAfterCapture = bbAll & (~Bitboard::square(square)) &
                                             (~Bitboard::square(enPassantSq).shifted(relativeDirection(them, NORTH)));
            if ((Bitboard::slidingAttacks(ourKing, occupancyAfterCapture, Bitboard::rank(ourKing)) &
                theirOrthogonalSliders) == 0)
                // when the pawn is not pinned, but en-passant discovers an orthogonal slider check
            {
                list.push_back(Move(square, enPassantSq, Move::EN_PASSANT));
            }
        }

        Bitboard pinnedCandidates = Bitboard::pawnAttacksTo(them, enPassantSq) & pinnedPawns
                                    & Bitboard::line(enPassantSq, ourKing);
        while (pinnedCandidates) // there can only be 1 such candidate - optimize it
        {
            list.push_back(Move(pinnedCandidates.popLsb(), enPassantSq, Move::EN_PASSANT));
        }
    }

    // generate promotions
    {
        {
            Bitboard nonPinnedCandidates = nonPinnedPawns & relativeRank7;
            while (nonPinnedCandidates)
            {
                Square sq = nonPinnedCandidates.popLsb();

                Bitboard attacks = Bitboard::pawnAttacksTo(us, sq) & captureMask;
                generateMoves<Move::Type::PROMOTION_CAPTURE>(list, sq, attacks);

                Bitboard push = Bitboard::square(sq).shifted(relativeDirection(us, NORTH)) & quietMask;
                generateMoves<Move::Type::PROMOTION>(list, sq, push);
            }
        }

        {
            Bitboard pinnedCandidates = pinnedPawns & relativeRank7;
            while (pinnedCandidates)
            {
                Square sq = pinnedCandidates.popLsb();

                Bitboard attacks = Bitboard::pawnAttacksTo(us, sq) & captureMask & Bitboard::line(sq, ourKing);
                generateMoves<Move::Type::PROMOTION_CAPTURE>(list, sq, attacks);

                Bitboard push = Bitboard::square(sq).shifted(relativeDirection(us, NORTH)) & quietMask & Bitboard::line(sq, ourKing);
                generateMoves<Move::Type::PROMOTION>(list, sq, push);
            }
        }
    }

    // generate non-promotion captures and pushes
    {
        {
            Bitboard nonPinnedCandidates = nonPinnedPawns & (~relativeRank7);
            while (nonPinnedCandidates)
            {
                Square sq = nonPinnedCandidates.popLsb();

                Bitboard attacks = Bitboard::pawnAttacksTo(us, sq) & captureMask;
                generateMoves<Move::Type::CAPTURE>(list, sq, attacks);

                Bitboard push = Bitboard::square(sq).shifted(relativeDirection(us, NORTH)) & quietMask;
                generateMoves<Move::Type::QUIET>(list, sq, push);
            }
        }

        {
            Bitboard pinnedCandidates = pinnedPawns & (~relativeRank7);
            while (pinnedCandidates)
            {
                Square sq = pinnedCandidates.popLsb();

                Bitboard attacks = Bitboard::pawnAttacksTo(us, sq) & captureMask & Bitboard::line(ourKing, sq);
                generateMoves<Move::Type::CAPTURE>(list, sq, attacks);

                Bitboard push = Bitboard::square(sq).shifted(relativeDirection(us, NORTH)) & quietMask & Bitboard::line(ourKing, sq);
                generateMoves<Move::Type::QUIET>(list, sq, push);
            }
        }
    }

    // generate double pushes
    {
        {
            Bitboard pinnedSecondRank = pinnedPawns & relativeRank2;
            while (pinnedSecondRank)
            {
                Square sq = pinnedSecondRank.popLsb();
                if (position.mailbox[sq + relativeDirection(us, NORTH)] == NULL_PIECE)
                    generateMoves<Move::DOUBLE_PUSH>(list, sq, relativeRank4 & quietMask & Bitboard::line(sq, ourKing) & Bitboard::file(sq));
            }
        }

        {
            Bitboard nonPinnedSecondRank = nonPinnedPawns & relativeRank2;
            while (nonPinnedSecondRank)
            {
                Square sq = nonPinnedSecondRank.popLsb();
                if (position.mailbox[sq + relativeDirection(us, NORTH)] == NULL_PIECE)
                    generateMoves<Move::DOUBLE_PUSH>(list, sq, relativeRank4 & quietMask & Bitboard::file(sq));
            }
        }
    }
}

void MoveGenerator::generateKnightMoves(MoveList &list, const Position &position, Bitboard quietMask, Bitboard captureMask, Bitboard pinned)
{
    const Color us = position.sideToPlay;

    Bitboard ourKnights = position.pieceBB[makePiece(us, KNIGHT)] & (~pinned);

    while (ourKnights)
    {
        Square knight = ourKnights.popLsb();
        Bitboard knightAttacks = Bitboard::knightAttacks(knight);

        generateMoves<Move::Type::CAPTURE>(list, knight, knightAttacks & captureMask);
        generateMoves<Move::Type::QUIET>(list, knight, knightAttacks & quietMask);
    }
}

void MoveGenerator::generateSlidingMoves(MoveList &list, const Position &position, Bitboard quietMask, Bitboard captureMask, Bitboard pinned)
{
    const Color us = position.sideToPlay;
    const Color them = ~us;

    const Bitboard bbUs = position.getPieces(us);
    const Bitboard bbThem = position.getPieces(them);
    const Bitboard bbAll = bbUs | bbThem;

    const Square ourKing = position.pieceBB[makePiece(us, KING)].lsb();

    const Bitboard ourOrthogonalSliders = position.getOrthogonalSliders(us);
    const Bitboard ourDiagonalSliders = position.getDiagonalSliders(us);

    {
        Bitboard pinnedDiagonal = ourDiagonalSliders & pinned;
        while (pinnedDiagonal)
        {
            Square pieceSq = pinnedDiagonal.popLsb();
            // only in the LINE direction
            Bitboard diagAttacks = Bitboard::bishopAttacks(pieceSq, bbAll) & Bitboard::line(ourKing, pieceSq);

            generateMoves<Move::Type::CAPTURE>(list, pieceSq, diagAttacks & captureMask);
            generateMoves<Move::Type::QUIET>(list, pieceSq, diagAttacks & quietMask);
        }
    }

    {
        Bitboard nonPinnedDiagonal = ourDiagonalSliders & (~pinned);
        while (nonPinnedDiagonal)
        {
            Square pieceSq = nonPinnedDiagonal.popLsb();
            Bitboard diagAttacks = Bitboard::bishopAttacks(pieceSq, bbAll);

            generateMoves<Move::Type::CAPTURE>(list, pieceSq, diagAttacks & captureMask);
            generateMoves<Move::Type::QUIET>(list, pieceSq, diagAttacks & quietMask);
        }
    }

    {
        Bitboard pinnedOrthogonal = ourOrthogonalSliders & pinned;
        while (pinnedOrthogonal)
        {
            Square pieceSq = pinnedOrthogonal.popLsb();
            // only in the LINE direction
            Bitboard orthAttacks = Bitboard::rookAttacks(pieceSq, bbAll) & Bitboard::line(ourKing, pieceSq);

            generateMoves<Move::Type::CAPTURE>(list, pieceSq, orthAttacks & captureMask);
            generateMoves<Move::Type::QUIET>(list, pieceSq, orthAttacks & quietMask);
        }
    }

    {
        Bitboard nonPinnedOrthogonal = ourOrthogonalSliders & (~pinned);
        while (nonPinnedOrthogonal)
        {
            Square pieceSq = nonPinnedOrthogonal.popLsb();
            Bitboard orthAttacks = Bitboard::rookAttacks(pieceSq, bbAll);

            generateMoves<Move::Type::CAPTURE>(list, pieceSq, orthAttacks & captureMask);
            generateMoves<Move::Type::QUIET>(list, pieceSq, orthAttacks & quietMask);
        }
    }
}

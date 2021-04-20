//
// Created by mikhail on 11.04.21.
//

#include <sstream>
#include "../BoardRepresentation/Position.h"
#include "FenUtility.h"
#include "../BoardRepresentation/Direction.h"
#include "../BoardRepresentation/BB.h"

const std::string FenUtility::DEFAULT_FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
const std::string FenUtility::KIWIPETE_FEN = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1";
const std::string FenUtility::TEST3_FEN = "8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 1";
const std::string FenUtility::TEST4_FEN = "r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1";
const std::string FenUtility::TEST5_FEN = "rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8";
const std::string FenUtility::TEST6_FEN = "r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10";

void FenUtility::set(Position &pos, const std::string &fen)
{
    pos.clear();

    size_t spaceChar = 0;
    size_t nextSpaceChar = fen.find(' ' , spaceChar);
    std::string pieces = fen.substr(spaceChar, nextSpaceChar - spaceChar);

    spaceChar = nextSpaceChar;
    nextSpaceChar = fen.find(' ' , spaceChar + 1);
    std::string sideToPlay = fen.substr(spaceChar + 1, nextSpaceChar - spaceChar - 1);

    spaceChar = nextSpaceChar;
    nextSpaceChar = fen.find(' ' , spaceChar + 1);
    std::string castleRights = fen.substr(spaceChar + 1, nextSpaceChar - spaceChar - 1);

    spaceChar = nextSpaceChar;
    nextSpaceChar = fen.find(' ' , spaceChar + 1);
    std::string enPassantSquare = fen.substr(spaceChar + 1, nextSpaceChar - spaceChar - 1);

    spaceChar = nextSpaceChar;
    nextSpaceChar = fen.find(' ' , spaceChar + 1);
    std::string halfMoveClock = fen.substr(spaceChar + 1, nextSpaceChar - spaceChar - 1);

    spaceChar = nextSpaceChar;
    std::string fullMoves = fen.substr(spaceChar + 1);

    // set side to play
    pos.sideToPlay = (sideToPlay == "w" ? WHITE : BLACK);

    // set game ply
    pos.gamePly = (std::stoi(fullMoves) - 1) * 2 + static_cast<int>(pos.sideToPlay);

    // set EP square
    {
        Square square = static_cast<Square>(std::find(SQUARE_STRING, SQUARE_STRING + NUMBER_OF_SQUARES, enPassantSquare) - SQUARE_STRING);
        pos.history[pos.gamePly].enPassantSquare = square != NUMBER_OF_SQUARES ? square : NULL_SQUARE;
    }

    // set 50 move rule counter
    pos.history[pos.gamePly].plyFiftyMoveRule = std::stoi(halfMoveClock);

    // set pieces
    Square square = A8;
    for (char ch: pieces)
    {
        if (isdigit(ch))
        {
            square = static_cast<Square>(square + static_cast<int>(ch - '0') * static_cast<int>(EAST));
        }
        else if (ch == '/')
        {
            square = static_cast<Square>(square + 2 * static_cast<int>(SOUTH));
        }
        else
        {
            pos.putPiece(static_cast<Piece>(PIECE_CHAR.find(ch)), square);
            ++square;
        }
    }

    // set castle rights
    pos.history[pos.gamePly].movedPieces = BB::ALL_CASTLING_MASK;
    for (char token: castleRights)
    {
        switch (token)
        {
            case 'K':
                pos.history[pos.gamePly].movedPieces &= ~BB::WHITE_CASTLING_00_MASK;
                break;
            case 'Q':
                pos.history[pos.gamePly].movedPieces &= ~BB::WHITE_CASTLING_000_MASK;
                break;
            case 'k':
                pos.history[pos.gamePly].movedPieces &= ~BB::BLACK_CASTLING_00_MASK;
                break;
            case 'q':
                pos.history[pos.gamePly].movedPieces &= ~BB::BLACK_CASTLING_000_MASK;
                break;
        }
    }
}

std::string FenUtility::fen(const Position &position)
{
    std::string fen;

    for (int i = 56; i >= 0; i -= 8)
    {
        uint32_t empty = 0;
        for (int j = 0; j < 8; ++j)
        {
            Piece piece = position.mailbox[i + j];
            if (piece == NULL_PIECE)
            {
                ++empty;
            }
            else
            {
                fen += (empty == 0 ? "" : std::to_string(empty)) + PIECE_CHAR[piece];
                empty = 0;
            }
        }

        if (empty != 0)
        {
            fen += std::to_string(empty);
        }
        if (i > 0)
        {
            fen += '/';
        }
    }

    fen += (position.sideToPlay == WHITE ? " w " : " b ");
    int castlings = 0;
    if (!(position.history[position.gamePly].movedPieces & BB::WHITE_CASTLING_00_MASK)) { fen += "K"; ++castlings; }
    if (!(position.history[position.gamePly].movedPieces & BB::WHITE_CASTLING_000_MASK)) { fen += "Q"; ++castlings; }
    if (!(position.history[position.gamePly].movedPieces & BB::BLACK_CASTLING_00_MASK)) { fen += "k"; ++castlings; }
    if (!(position.history[position.gamePly].movedPieces & BB::BLACK_CASTLING_000_MASK)) { fen += "q"; ++castlings; }
    if (castlings == 0) fen += "-";

    fen += (position.history[position.gamePly].enPassantSquare == NULL_SQUARE ? " -" : " " + SQUARE_STRING[position.history[position.gamePly].enPassantSquare]);
    fen += " " + std::to_string(position.history[position.gamePly].plyFiftyMoveRule);
    fen += " " + std::to_string(position.gamePly / 2 + 1);

    return fen;
}

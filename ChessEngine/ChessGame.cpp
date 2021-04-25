#include "ChessGame.h"
#include <iostream>
#include <Utility/Zobrist.h>
#include <BoardRepresentation/BB.h>

ChessGame::ChessGame(Player * white, Player * black)
    : whitePlayer(white)
    , blackPlayer(black)
{

}

void ChessGame::play(const std::string & fen)
{
    Position pos(fen);

    while (pos.status() == Position::NOT_FINISHED)
    {
        std::cout << pos << std::endl;
        if (pos.sideToPlay == WHITE)
        {
            whitePlayer->makeMove(pos);
        }
        else
        {
            blackPlayer->makeMove(pos);
        }
    }

    std::cout << pos << std::endl;

    switch (pos.status())
    {
    case Position::DRAW:
        std::cout << "Game finished with draw" << std::endl;
        break;

    case Position::STALEMATE:
        std::cout << "Game finished with stalemate" << std::endl;
        break;

    case Position::WHITE_WIN:
        std::cout << "White won the game" << std::endl;
        break;

    case Position::BLACK_WIN:
        std::cout << "Black won the game" << std::endl;
        break;

    case Position::NOT_FINISHED:
        std::cout << "Game wasn't finished" << std::endl;
        break;
    }
}

#include "ChessGame.h"
#include <iostream>
#include <Utility/Zobrist.h>
#include <BoardRepresentation/BB.h>

ChessGame::ChessGame(Player * white, Player * black)
    : whitePlayer(white)
    , blackPlayer(black)
    , m_result(0)
{

}

void ChessGame::play(const std::string & fen)
{
    Position pos(fen);

    while (pos.status() == Position::NOT_FINISHED)
    {
//        std::cout << pos << std::endl;
        if (pos.sideToPlay == WHITE)
        {
            whitePlayer->makeMove(pos);
        }
        else
        {
            blackPlayer->makeMove(pos);
        }
    }

//    std::cout << pos << std::endl;

    switch (pos.status())
    {
    case Position::DRAW:
        m_result = 0;
//        std::cout << "Game finished with draw" << std::endl;
        break;

    case Position::STALEMATE:
        m_result = 0;
//        std::cout << "Game finished with stalemate" << std::endl;
        break;

    case Position::WHITE_WIN:
        m_result = 1;
//        std::cout << "White won the game" << std::endl;
        break;

    case Position::BLACK_WIN:
        m_result = -1;
//        std::cout << "Black won the game" << std::endl;
        break;

    case Position::NOT_FINISHED:
        throw std::runtime_error("AAAA");
//        std::cout << "Game wasn't finished" << std::endl;
        break;
    }
}

int ChessGame::result() const
{
    return m_result;
}

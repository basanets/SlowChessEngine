#include "HumanPlayer.h"
#include <iostream>
#include <BoardRepresentation/Position.h>

Move HumanPlayer::makeMove(Position & position)
{
    if (position.status() != Position::NOT_FINISHED)
    {
        throw std::runtime_error("Cannot make the move - the game is finished");
    }

    std::string moveString;
    std::cout << "Enter your move (pure coord notation): ";
    std::cin >> moveString;

    Move move = position.moveFromString(moveString);
    position.makeMove(move);

    std::cout << "[HUMAN]: Played a move: " << move.toString() << std::endl;

    return move;
}

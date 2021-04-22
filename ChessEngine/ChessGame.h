#ifndef CHESSGAME_H
#define CHESSGAME_H

#include "Player.h"

#include <BoardRepresentation/Position.h>

class ChessGame
{
public:
    ChessGame(Player * white, Player * black);

public:
    void play(const std::string & fen = FenUtility::DEFAULT_FEN);

private:
    Player * whitePlayer;
    Player * blackPlayer;
};

#endif // CHESSGAME_H

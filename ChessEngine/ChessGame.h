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
    int result() const;

private:
    int m_result;
    Player * whitePlayer;
    Player * blackPlayer;
};

#endif // CHESSGAME_H

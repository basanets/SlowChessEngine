#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "Player.h"

class HumanPlayer : public Player
{
public:
    HumanPlayer() = default;
    ~HumanPlayer() override = default;

public:
    Move makeMove(Position & position) override;
};

#endif // HUMANPLAYER_H

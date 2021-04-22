#ifndef PLAYER_H
#define PLAYER_H

class Move;
class Position;

class Player
{
public:
    virtual ~Player() = default;

public:
    virtual Move makeMove(Position & position) = 0;
};

#endif // PLAYER_H

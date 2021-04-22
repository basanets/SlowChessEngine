#ifndef STATICEVALUATIONBOT_H
#define STATICEVALUATIONBOT_H

#include "Player.h"
#include <cstdint>

class StaticEvaluationBot: public Player
{
public:
    StaticEvaluationBot(uint32_t maxDepth);
    ~StaticEvaluationBot() override = default;

public:
    Move makeMove(Position & position) override;

private:
    uint32_t maxSearchDepth;
};

#endif // STATICEVALUATIONBOT_H

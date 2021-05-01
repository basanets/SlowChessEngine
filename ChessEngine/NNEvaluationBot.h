#ifndef NNEVALUATIONBOT_H
#define NNEVALUATIONBOT_H

#include <memory>
#include "Player.h"
#include <Evaluation/NeuralNetworkEvaluator.h>

class NNEvaluationBot : public Player
{
public:
    NNEvaluationBot(NeuralNetworkEvaluator * nnEvaluator, uint32_t maxSearchDepth = 3);
    ~NNEvaluationBot() override = default;

public:
    Move makeMove(Position & position) override;

private:
    NeuralNetworkEvaluator * neuralEvaluator;
    uint32_t maxSearchDepth;
};

#endif // NNEVALUATIONBOT_H

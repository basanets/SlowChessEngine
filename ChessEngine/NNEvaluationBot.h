#include "EngineConfig.h"

#ifdef USE_NN_EVALUATION

#ifndef NNEVALUATIONBOT_H
#define NNEVALUATIONBOT_H

#include <memory>
#include "Player.h"
#include <Evaluation/NeuralNetworkEvaluator.h>

class NNEvaluationBot : public Player
{
public:
    NNEvaluationBot(const std::string & pathToModel, uint32_t maxSearchDepth = 3);
    ~NNEvaluationBot() override = default;

public:
    Move makeMove(Position & position) override;

private:
    std::unique_ptr<NeuralNetworkEvaluator> neuralEvaluator;
    uint32_t maxSearchDepth;
};

#endif // NNEVALUATIONBOT_H

#endif // USE_NN_EVALUATION

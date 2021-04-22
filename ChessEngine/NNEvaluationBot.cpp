#include "EngineConfig.h"

#ifdef USE_NN_EVALUATION

#include "NNEvaluationBot.h"

#include <iostream>
#include <BoardRepresentation/Position.h>
#include <Search/DefaultSearcher.h>

NNEvaluationBot::NNEvaluationBot(const std::string & pathToModel, uint32_t maxSearchDepth)
    : neuralEvaluator(new NeuralNetworkEvaluator(pathToModel))
    , maxSearchDepth(maxSearchDepth)
{

}

Move NNEvaluationBot::makeMove(Position & position)
{
    if (position.status() != Position::NOT_FINISHED)
    {
        throw std::runtime_error("Cannot make the move - the game is finished");
    }

    DefaultSearcher moveSearcher(neuralEvaluator.get());
    const auto & [move, evaluation] = moveSearcher.iterativeDeepeningSearch(position, maxSearchDepth);
    std::cout << "[NNEvaluationBot]: Best move found: " << move.toString() << " with evaluation: " << evaluation << std::endl;
    position.makeMove(move);
    return move;
}

#endif // USE_NN_EVALUATION

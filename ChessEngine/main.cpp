#include <iostream>
#include "ChessGame.h"

#include "NNEvaluationBot.h"
#include "StaticEvaluationBot.h"

int main(int argc, char** argv)
{
    std::string modelPath = "/home/mikhail/university/SlowChessEngine/nn/evaluate_position_simplified";
    NNEvaluationBot nnBot(modelPath);
    if (argc > 1)
    {
        modelPath = std::string(argv[1]);
        std::cout << "Setting model path to " << modelPath;
    }

    StaticEvaluationBot staticBotWhite(4);
    StaticEvaluationBot staticBotBlack(6);
    ChessGame game(&staticBotWhite, &nnBot);
    game.play();

    return 0;
}

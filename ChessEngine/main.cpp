#include <chrono>
#include <iostream>
#include <Evaluation/SimpleEvaluator.h>
#include "ChessEngine.h"
#include "ChessGame.h"
#include "NNEvaluationBot.h"
#include "StaticEvaluationBot.h"

int main(int argc, char** argv)
{
    std::string modelPath = "/home/mikhail/university/SlowChessEngine/nn/evaluate_position_simplified";

//    if (argc > 1)
//    {
//        modelPath = std::string(argv[1]);
//        std::cout << "Setting model path to " << modelPath;
//    }

//    ChessEngine engine(modelPath);
//    return engine.exec();

    ChessEngine engine(modelPath);
    NeuralNetworkEvaluator nneval(modelPath);

    StaticEvaluationBot classicBot(2);
    NNEvaluationBot nnBot(&nneval, 2);

    int whiteWins;
    int draws;
    int blackWins;
    whiteWins = draws = blackWins = 0;
    std::cout << "\n\n\n\n"
                 "100 games between classic evaluation bot (white) and neural evaluation bot (black)\n\n";
    for (int i = 0; i < 100; ++i)
    {
        ChessGame game(&classicBot, &nnBot);
        game.play();
        if (game.result() > 0)
            whiteWins++;
        else if (game.result() == 0)
            draws++;
        else
            blackWins++;
    }
    std::cout << "White wins: " << whiteWins << std::endl;
    std::cout << "Draws: " << draws << std::endl;
    std::cout << "Black wins: " << blackWins << std::endl;


    whiteWins = draws = blackWins = 0;
    std::cout << "\n\n\n\n"
                 "100 games between neural evaluation bot (white) and classic evaluation bot (black)\n\n";
    for (int i = 0; i < 100; ++i)
    {
        ChessGame game(&nnBot, &classicBot);
        game.play();
        if (game.result() > 0)
            whiteWins++;
        else if (game.result() == 0)
            draws++;
        else
            blackWins++;
    }
    std::cout << "White wins: " << whiteWins << std::endl;
    std::cout << "Draws: " << draws << std::endl;
    std::cout << "Black wins: " << blackWins << std::endl;
}

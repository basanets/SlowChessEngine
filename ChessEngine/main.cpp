#include <iostream>
#include "ChessEngine.h"

int main(int argc, char** argv)
{
    std::string modelPath = "/home/mikhail/university/SlowChessEngine/nn/evaluate_position_simplified";

    if (argc > 1)
    {
        modelPath = std::string(argv[1]);
        std::cout << "Setting model path to " << modelPath;
    }

    ChessEngine engine(modelPath);
    return engine.exec();
}

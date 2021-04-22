#include <iostream>
#include <chrono>
#include <Search/DefaultSearcher.h>
#include "BoardRepresentation/Position.h"
#include "Utility/FenUtility.h"
#include "Utility/Zobrist.h"
#include "BoardRepresentation/BB.h"
#include "MoveGeneration/MoveList.h"
#include "Search/PerfomanceTester.h"

void play(Position & pos)
{
    Color human = WHITE;

    std::cout << pos << std::endl;

    const std::string modelFilePath = "/home/mikhail/university/SlowChessEngine/nn/evaluate_position";

    while (true)
    {
        if (pos.status() != Position::NOT_FINISHED)
        {
            std::cout << "game ended" << std::endl;
            break;
        }

        if (pos.sideToPlay == human)
        {
            std::string move;
            std::cin >> move;
            pos.makeMove(pos.moveFromString(move));
        }
        else
        {
            DefaultSearcher searcher;
            const auto & [bestMove, eval] = searcher.iterativeDeepeningSearch(pos, 2);
            std::cout << "Time taken: " << searcher.timeTaken / 1000000.0 << std::endl;
            std::cout << "Nodes reached: " << searcher.nodesReached << std::endl;
            std::cout << "Nodes evaluated: " << searcher.nodesEvaluated << std::endl;
            std::cout << "Nodes cutoff: " << searcher.nodesCutOff << std::endl;

            std::cout << bestMove.toString() << ": " << eval << std::endl;
            pos.makeMove(bestMove);
        }

        std::cout << pos << std::endl;
    }
}

int main()
{
    Zobrist::initializeTable();
    BB::initializeAll();

    Position position;
    play(position);

    return 0;
}

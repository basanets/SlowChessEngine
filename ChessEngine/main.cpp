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
    Color agent = BLACK;

    std::cout << pos << std::endl;

    while (true)
    {
        if (pos.sideToPlay == human)
        {
            std::string move;
            std::cin >> move;
            pos.makeMove(pos.moveFromString(move));
        }
        else
        {
            DefaultSearcher searcher;
            const auto & [bestMove, eval] = searcher.findBestMove(pos, 6);
            std::cout << "Time taken: " << searcher.timeTaken / 1000000.0 << std::endl;
            std::cout << "Nodes reached: " << searcher.nodesReached << std::endl;
            std::cout << "Nodes evaluated: " << searcher.nodesEvaluated << std::endl;
            std::cout << "Nodes cutoff: " << searcher.nodesCutOff << std::endl;

            if (bestMove.from() != NULL_SQUARE && !(pos.history[pos.gamePly].plyFiftyMoveRule == 50))
            {
                std::cout << bestMove.toString() << ": " << eval << std::endl;
                pos.makeMove(bestMove);
            }
            else
            {
                std::cout << "game ended" << std::endl;
                break;
            }
        }

        std::cout << pos << std::endl;
    }
}

int main()
{
    Zobrist::initializeTable();
    BB::initializeAll();

    Position position/*("rnbq1rk1/ppppbppp/5n2/8/4P1P1/6p1/PPPP1B1P/RNBQK1NR w - - 0 7")*/;
    std::cout << position << std::endl;
    std::string move;
    while (std::cin >> move)
    {
        position.makeMove(position.moveFromString(move));
        std::cout << position << std::endl;
    }

    return 0;
}

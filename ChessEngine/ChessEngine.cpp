#include "ChessEngine.h"

#include <Utility/Zobrist.h>
#include <BoardRepresentation/BB.h>
#include <Evaluation/NeuralNetworkEvaluator.h>
#include <Search/DefaultSearcher.h>
#include <Search/PerfomanceTester.h>
#include <Search/PrincipalVariationSearcher.h>
#include <chrono>

ChessEngine::ChessEngine(const std::string & pathToModel)
{
    Zobrist::initializeTable();
    BB::initializeAll();
    chessPosition.set(FenUtility::DEFAULT_FEN);
    nnEvaluator = std::make_unique<NeuralNetworkEvaluator>(pathToModel);
    std::cout << "\n\n\nEngine started!\n\n" << std::endl;
}

int ChessEngine::exec()
{
    std::string command = "";
    while (command != "exit")
    {
        command = waitForUserInput(std::cin);
        if (command == "exit")
        {
            std::cout << "Shutting down" << std::endl;
        }
        else
        {
            auto start = std::chrono::system_clock::now();
            executeCommand(command);
            auto finish = std::chrono::system_clock::now();
            double timeTaken = std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count() / 1000000.0;
            std::cout << "Time taken: " << timeTaken << "\n\n" << std::endl;
        }
    }
    return 0;
}

void ChessEngine::executeCommand(const std::string & command)
{
    if (command.starts_with("position"))
    {
        const std::string fen = command.substr(command.find(' ') + 1);
        chessPosition.set(fen);
    }
    else if (command == "d")
    {
        std::cout << chessPosition << std::endl;
    }
    else if (command == "generate")
    {
        MoveList moveList(chessPosition);
        for (Move move: moveList)
            std::cout << move.toString() << std::endl;
    }
    else if (command.starts_with("perftdiv"))
    {
        uint32_t depth = std::stoi(command.substr(command.find(' ')));
        uint64_t totalNodes = PerfomanceTester::perftdiv(chessPosition, depth);
        std::cout << "Total nodes: " << totalNodes << std::endl;
    }
    else if (command.starts_with("perft"))
    {
        uint32_t depth = std::stoi(command.substr(command.find(' ')));
        uint64_t totalNodes = PerfomanceTester::perft(chessPosition, depth);
        std::cout << "Total nodes: " << totalNodes << std::endl;
    }
    else if (command.starts_with("findnn"))
    {
        uint32_t depth = std::stoi(command.substr(command.find(' ')));
        PrincipalVariationSearcher searcher(nnEvaluator.get());
        const auto [move, eval] = searcher.iterativeDeepeningSearch(chessPosition, depth);
        std::cout << "Best move: " << move.toString() << std::endl;
        std::cout << "Evaluation: " << eval << std::endl;
        std::cout << "Max depth with quiet search: " << searcher.getMaxDepth() << std::endl;
    }
    else if (command.starts_with("find"))
    {
        uint32_t depth = std::stoi(command.substr(command.find(' ')));
        PrincipalVariationSearcher searcher(nullptr);
        const auto [move, eval] = searcher.iterativeDeepeningSearch(chessPosition, depth);
        std::cout << "Best move: " << move.toString() << std::endl;
        std::cout << "Evaluation: " << eval << std::endl;
        std::cout << "Max depth with quiet search: " << searcher.getMaxDepth() << std::endl;
    }
    else
    {
        std::cout << "Unknown command" << std::endl;
    }
}

std::string ChessEngine::waitForUserInput(std::istream & is)
{
    std::string command;
    std::getline(is, command);
    return command;
}

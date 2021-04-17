#include <iostream>
#include <chrono>
#include "BoardRepresentation/Position.h"
#include "Utility/FenUtility.h"
#include "Utility/Zobrist.h"
#include "BoardRepresentation/BB.h"
#include "MoveGeneration/MoveList.h"
#include "Search/PerfomanceTester.h"

void runTest(Position & pos, uint32_t depth)
{
    auto start = std::chrono::steady_clock::now();
    std::cout << PerfomanceTester::perft(pos, depth) << std::endl;
    auto finish = std::chrono::steady_clock::now();
    std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count() / 1000.0 << "\n\n\n" << std::endl;
}

int main()
{
    Zobrist::initializeTable();
    BB::initializeAll();

    Position position;

    position.set(FenUtility::DEFAULT_FEN);
    runTest(position, 5);
    runTest(position, 6);
//    runTest(position, 7);
//    position.set(FenUtility::KIWIPETE_FEN);
//    runTest(position, 5);
//    position.set(FenUtility::TEST3_FEN);
//    runTest(position, 7);
//    position.set(FenUtility::TEST4_FEN);
//    runTest(position, 6);
//    position.set(FenUtility::TEST5_FEN);
//    runTest(position, 5);
//    position.set(FenUtility::TEST6_FEN);
//    runTest(position, 5);

    return 0;
}

#include <iostream>
#include <chrono>
#include "BoardRepresentation/Position.h"
#include "Utility/FenUtility.h"
#include "Utility/Zobrist.h"
#include "BoardRepresentation/BB.h"
#include "MoveGeneration/MoveList.h"

//void play(Position & pos)
//{
//    std::cout << pos;
//
//    std::string move;
//    std::cin >> move;
//
//    std::stack<Move> history;
//
//    while (move.size() >= 4)
//    {
//
//        const Square from = static_cast<Square>(std::find(SQUARE_STRING, SQUARE_STRING + NUMBER_OF_SQUARES, move.substr(0, 2)) - SQUARE_STRING);
//        const Square to   = static_cast<Square>(std::find(SQUARE_STRING, SQUARE_STRING + NUMBER_OF_SQUARES, move.substr(2, 2)) - SQUARE_STRING);
//        Move::Type type = Move::QUIET;
//
//        std::string typeString = move.substr(4);
//        if (typeString == "ep") type = Move::EN_PASSANT;
//        else if (typeString == "c") type = Move::CAPTURE;
//        else if (typeString == "dp") type = Move::DOUBLE_PUSH;
//        else if (typeString == "00") type = Move::CASTLE_00;
//        else if (typeString == "000") type = Move::CASTLE_000;
//        else if (typeString == "pr") type = Move::PROMOTION_ROOK;
//        else if (typeString == "pn") type = Move::PROMOTION_KNIGHT;
//        else if (typeString == "pb") type = Move::PROMOTION_BISHOP;
//        else if (typeString == "pq") type = Move::PROMOTION_QUEEN;
//        else if (typeString == "prc") type = Move::PROMOTION_CAPTURE_ROOK;
//        else if (typeString == "pnc") type = Move::PROMOTION_CAPTURE_KNIGHT;
//        else if (typeString == "pbc") type = Move::PROMOTION_CAPTURE_BISHOP;
//        else if (typeString == "pqc") type = Move::PROMOTION_CAPTURE_QUEEN;
//
//        if (move == "undo")
//        {
//            if (history.empty())
//            {
//                continue;
//            }
//            else
//            {
//                pos.undoMove(history.top());
//                history.pop();
//            }
//        }
//        else
//        {
//            history.push(Move(from, to, type));
//            pos.makeMove(Move(from, to, type));
//        }
//
//        std::cout << pos;
//        std::cin >> move;
//    }
//
//}

uint64_t perft(Position & p, uint32_t depth)
{
    if (depth == 0) return 1;
    uint64_t nodes = 0;

    MoveList list(p);

    if (depth == 1) return list.size();

    for (Move move: list)
    {
        p.makeMove(move);
        nodes += perft(p, depth - 1);
        p.undoMove(move);
    }

    return nodes;
}

uint64_t perftdiv(Position & p, uint32_t depth)
{
    MoveList list(p);
    uint64_t totalNodes = 0;
    for (Move move: list)
    {
        p.makeMove(move);
        uint64_t nodes = perft(p, depth - 1);
        std::cout << move.toString() << ": " << nodes << std::endl;
        totalNodes += nodes;
        p.undoMove(move);
    }

    return totalNodes;
}

void runTest(Position & pos, uint32_t depth)
{
    auto start = std::chrono::steady_clock::now();
    std::cout << perft(pos, depth) << std::endl;
    auto finish = std::chrono::steady_clock::now();
    std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count() / 1000.0 << "\n\n\n" << std::endl;
}

int main()
{
    Zobrist::initializeTable();
    BB::initializeAll();

    Position position("rnbqkb1r/pp1p1ppp/2p5/4P3/2B5/8/PPP1NnPP/RNBQK2R w KQkq - 0 6");
    std::cout << position << std::endl;

    runTest(position, 1);
    runTest(position, 2);
    runTest(position, 3);
    runTest(position, 4);
    runTest(position, 5);
    runTest(position, 6);
    runTest(position, 7);

    return 0;
}

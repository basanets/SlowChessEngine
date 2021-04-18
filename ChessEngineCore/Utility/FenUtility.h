//
// Created by mikhail on 11.04.21.
//

#ifndef CHESSENGINE_FENUTILITY_H
#define CHESSENGINE_FENUTILITY_H

#include <string>
class Position;

class FenUtility
{
public:
    static void set(Position & pos, const std::string & fen);
    static std::string fen(const Position & position);

//    https://www.chessprogramming.org/Perft_Results
    static const std::string DEFAULT_FEN;
    static const std::string KIWIPETE_FEN;
    static const std::string TEST3_FEN;
    static const std::string TEST4_FEN;
    static const std::string TEST5_FEN;
    static const std::string TEST6_FEN;
};


#endif //CHESSENGINE_FENUTILITY_H

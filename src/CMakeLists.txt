cmake_minimum_required(VERSION 3.19)
project(ChessEngine)

set(CMAKE_CXX_STANDARD 20)

add_executable(ChessEngine main.cpp BoardRepresentation/Bitboard.cpp BoardRepresentation/Bitboard.h BoardRepresentation/Color.h BoardRepresentation/Direction.h BoardRepresentation/Piece.h BoardRepresentation/Square.h BoardRepresentation/Position.cpp BoardRepresentation/Position.h Utility/Zobrist.cpp Utility/Zobrist.h BoardRepresentation/Move.cpp BoardRepresentation/Move.h Utility/FenUtility.cpp Utility/FenUtility.h BoardRepresentation/BB.cpp BoardRepresentation/BB.h MoveGeneration/MoveGenerator.cpp MoveGeneration/MoveGenerator.h MoveGeneration/MoveList.h MoveGeneration/MoveList.cpp Search/PerfomanceTester.cpp Search/PerfomanceTester.h)

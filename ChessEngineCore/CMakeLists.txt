cmake_minimum_required(VERSION 3.19)
project(ChessEngineCore LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(USE_NN_EVALUATION "Compile the neural network evaluation functionality" ON)
configure_file(CoreConfig.h.in CoreConfig.h)

add_library(ChessEngineCore
    BoardRepresentation/Bitboard.cpp
    BoardRepresentation/Bitboard.h
    BoardRepresentation/Color.h
    BoardRepresentation/Direction.h
    BoardRepresentation/Piece.h
    BoardRepresentation/Square.h
    BoardRepresentation/Position.cpp
    BoardRepresentation/Position.h
    Utility/Zobrist.cpp
    Utility/Zobrist.h
    BoardRepresentation/Move.cpp
    BoardRepresentation/Move.h
    Utility/FenUtility.cpp
    Utility/FenUtility.h
    BoardRepresentation/BB.cpp
    BoardRepresentation/BB.h
    MoveGeneration/MoveGenerator.cpp
    MoveGeneration/MoveGenerator.h
    MoveGeneration/MoveList.h
    MoveGeneration/MoveList.cpp
    Search/PerfomanceTester.cpp
    Search/PerfomanceTester.h
    Evaluation/SimpleEvaluator.cpp
    Evaluation/SimpleEvaluator.h
    Search/DefaultSearcher.cpp
    Search/DefaultSearcher.h
    Search/TranspositionTable.cpp
    Search/TranspositionTable.h
    Evaluation/NeuralNetworkEvaluator.cpp
    Evaluation/NeuralNetworkEvaluator.h)

if (USE_NN_EVALUATION)
    find_library(TENSORFLOW_LIB tensorflow HINT $ENV{HOME}/libtensorflow2/lib)
    target_link_libraries (ChessEngineCore "${TENSORFLOW_LIB}")
endif()

target_compile_definitions(ChessEngineCore PRIVATE CHESSENGINECORE_LIBRARY)
target_include_directories(ChessEngineCore PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           ${EXTRA_INCLUDES}
                           )

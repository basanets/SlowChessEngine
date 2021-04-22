cmake_minimum_required(VERSION 3.19)
project(ChessEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ChessEngine
               main.cpp
               Player.h
               StaticEvaluationBot.cpp
               StaticEvaluationBot.h
               HumanPlayer.cpp
               HumanPlayer.h
               NNEvaluationBot.cpp
               NNEvaluationBot.h
               ChessGame.cpp
               ChessGame.h)

target_link_libraries(ChessEngine PRIVATE ChessEngineCore)
target_include_directories(ChessEngine PRIVATE
                            ../ChessEngineCore
                            "${PROJECT_BINARY_DIR}")

configure_file(EngineConfig.h.in EngineConfig.h)

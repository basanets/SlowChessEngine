#ifndef CHESSENGINE_H
#define CHESSENGINE_H

#include <iostream>
#include <BoardRepresentation/Position.h>
#include <memory>
#include <Evaluation/NeuralNetworkEvaluator.h>

class ChessEngine
{
public:
    explicit ChessEngine(const std::string & pathToModel);

public:
    int exec();
    void executeCommand(const std::string & command);
public:
    std::string waitForUserInput(std::istream & is);
    Position chessPosition;

private:
    std::unique_ptr<NeuralNetworkEvaluator> nnEvaluator;
};

#endif // CHESSENGINE_H

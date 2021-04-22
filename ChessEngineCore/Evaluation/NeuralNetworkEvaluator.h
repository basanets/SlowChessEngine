#ifndef NEURALNETWORKEVALUATOR_H
#define NEURALNETWORKEVALUATOR_H

#include <memory>
#include <BoardRepresentation/Color.h>
#include <cppflow/model.h>

class Position;

class NeuralNetworkEvaluator
{
public:
    NeuralNetworkEvaluator(const std::string & modelFilePath);

    int32_t evaluate(const Position & position);
    int32_t evaluate(const Position & position, Color color);

private:
    std::unique_ptr<cppflow::model> m_model;
};

#endif // NEURALNETWORKEVALUATOR_H

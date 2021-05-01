#include "NeuralNetworkEvaluator.h"

#include <BoardRepresentation/Position.h>

NeuralNetworkEvaluator::NeuralNetworkEvaluator(const std::string & modelFilePath)
    : m_model(new cppflow::model(modelFilePath))
{

}

int32_t NeuralNetworkEvaluator::evaluate(const Position & position)
{
    const static std::vector<int64_t> shape = {1, 1, 768};
    float normalizeFactor = 1000.0;

    cppflow::tensor input = cppflow::tensor(position.binaryFeatures(), shape);
    cppflow::tensor output = m_model->operator()(input);

    int32_t evaluation = output.get_data<float>().front() * normalizeFactor;
    return evaluation;
}

int32_t NeuralNetworkEvaluator::evaluate(const Position & position, Color color)
{
    return (color == WHITE) ? evaluate(position) : -evaluate(position);
}

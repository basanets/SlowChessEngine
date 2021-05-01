#include "StaticEvaluationBot.h"

#include <BoardRepresentation/Position.h>
#include <iostream>
#include <Search/DefaultSearcher.h>
#include <Search/PrincipalVariationSearcher.h>

StaticEvaluationBot::StaticEvaluationBot(uint32_t maxDepth)
    : maxSearchDepth(maxDepth)
{

}

Move StaticEvaluationBot::makeMove(Position & position)
{
    if (position.status() != Position::NOT_FINISHED)
    {
        throw std::runtime_error("Cannot make the move - the game is finished");
    }

    PrincipalVariationSearcher moveSearcher;
    const auto & [move, evaluation] = moveSearcher.iterativeDeepeningSearch(position, maxSearchDepth);
//    std::cout << "[StaticEvaluationBot]: Best move found: " << move.toString() << " with evaluation: " << evaluation << std::endl;
    position.makeMove(move);
    return move;
}

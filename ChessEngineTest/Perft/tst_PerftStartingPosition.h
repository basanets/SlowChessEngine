#ifndef TST_PERFTSTARTINGPOSITION_H
#define TST_PERFTSTARTINGPOSITION_H

#include <gtest/gtest.h>

#include <Utility/Zobrist.h>
#include <BoardRepresentation/BB.h>
#include <BoardRepresentation/Position.h>
#include <Search/PerfomanceTester.h>

class PerftStartingPosition:
        public ::testing::TestWithParam<std::pair<uint32_t, uint64_t>>
{
public:
    static void SetUpTestSuite()
    {
        Zobrist::initializeTable();
        BB::initializeAll();
    }
};

INSTANTIATE_TEST_SUITE_P(StartingPosition,
                         PerftStartingPosition,
                         ::testing::Values(
                               std::make_pair<uint32_t, uint64_t>(0, 1ull)
                             , std::make_pair<uint32_t, uint64_t>(1, 20ull)
                             , std::make_pair<uint32_t, uint64_t>(2, 400ull)
                             , std::make_pair<uint32_t, uint64_t>(3, 8902ull)
                             , std::make_pair<uint32_t, uint64_t>(4, 197281ull)
                             , std::make_pair<uint32_t, uint64_t>(5, 4865609ull)
                             , std::make_pair<uint32_t, uint64_t>(6, 119060324ull)
                             , std::make_pair<uint32_t, uint64_t>(7, 3195901860ull)
                             ));

TEST_P(PerftStartingPosition, AtDepth)
{
    Position position(FenUtility::DEFAULT_FEN);

    const auto & [perftDepth, expectedResult] = GetParam();

    ASSERT_EQ(PerfomanceTester::perft(position, perftDepth), expectedResult);
}

#endif // TST_PERFTSTARTINGPOSITION_H

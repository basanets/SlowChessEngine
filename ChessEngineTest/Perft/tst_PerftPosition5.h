#ifndef TST_PERFTPOSITION5_H
#define TST_PERFTPOSITION5_H

#include <gtest/gtest.h>

#include <Utility/Zobrist.h>
#include <BoardRepresentation/BB.h>
#include <BoardRepresentation/Position.h>
#include <Search/PerfomanceTester.h>

class PerftPosition5:
        public ::testing::TestWithParam<std::pair<uint32_t, uint64_t>>
{
public:
    static void SetUpTestSuite()
    {
        Zobrist::initializeTable();
        BB::initializeAll();
    }
};

INSTANTIATE_TEST_SUITE_P(Position5,
                         PerftPosition5,
                         ::testing::Values(
                             std::make_pair<uint32_t, uint64_t>(0, 1)
                           , std::make_pair<uint32_t, uint64_t>(1, 44)
                           , std::make_pair<uint32_t, uint64_t>(2, 1486)
                           , std::make_pair<uint32_t, uint64_t>(3, 62379)
                           , std::make_pair<uint32_t, uint64_t>(4, 2103487)
                           , std::make_pair<uint32_t, uint64_t>(5, 89941194)
                             ));

TEST_P(PerftPosition5, AtDepth)
{
    Position position(FenUtility::TEST5_FEN);

    const auto & [perftDepth, expectedResult] = GetParam();

    ASSERT_EQ(PerfomanceTester::perft(position, perftDepth), expectedResult);
}


#endif // TST_PERFTPOSITION5_H

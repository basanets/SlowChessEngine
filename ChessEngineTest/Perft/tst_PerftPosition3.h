#ifndef TST_PERFTPOSITION3_H
#define TST_PERFTPOSITION3_H

#include <gtest/gtest.h>

#include <Utility/Zobrist.h>
#include <BoardRepresentation/BB.h>
#include <BoardRepresentation/Position.h>
#include <Search/PerfomanceTester.h>

class PerftPosition3:
        public ::testing::TestWithParam<std::pair<uint32_t, uint64_t>>
{
public:
    static void SetUpTestSuite()
    {
        Zobrist::initializeTable();
        BB::initializeAll();
    }
};

INSTANTIATE_TEST_SUITE_P(Position3,
                         PerftPosition3,
                         ::testing::Values(
                             std::make_pair<uint32_t, uint64_t>(0, 1)
                           , std::make_pair<uint32_t, uint64_t>(1, 14)
                           , std::make_pair<uint32_t, uint64_t>(2, 191)
                           , std::make_pair<uint32_t, uint64_t>(3, 2812)
                           , std::make_pair<uint32_t, uint64_t>(4, 43238)
                           , std::make_pair<uint32_t, uint64_t>(5, 674624)
                           , std::make_pair<uint32_t, uint64_t>(6, 11030083)
                           , std::make_pair<uint32_t, uint64_t>(7, 178633661)
                           , std::make_pair<uint32_t, uint64_t>(8, 3009794393)
                             ));

TEST_P(PerftPosition3, AtDepth)
{
    Position position(FenUtility::TEST3_FEN);

    const auto & [perftDepth, expectedResult] = GetParam();

    ASSERT_EQ(PerfomanceTester::perft(position, perftDepth), expectedResult);
}

#endif // TST_PERFTPOSITION3_H

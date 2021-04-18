#ifndef TST_PERFTPOSITION4_H
#define TST_PERFTPOSITION4_H

#include <gtest/gtest.h>

#include <Utility/Zobrist.h>
#include <BoardRepresentation/BB.h>
#include <BoardRepresentation/Position.h>
#include <Search/PerfomanceTester.h>

class PerftPosition4:
        public ::testing::TestWithParam<std::pair<uint32_t, uint64_t>>
{
public:
    static void SetUpTestSuite()
    {
        Zobrist::initializeTable();
        BB::initializeAll();
    }
};

INSTANTIATE_TEST_SUITE_P(Position4,
                         PerftPosition4,
                         ::testing::Values(
                             std::make_pair<uint32_t, uint64_t>(0, 1)
                           , std::make_pair<uint32_t, uint64_t>(1, 6)
                           , std::make_pair<uint32_t, uint64_t>(2, 264)
                           , std::make_pair<uint32_t, uint64_t>(3, 9467)
                           , std::make_pair<uint32_t, uint64_t>(4, 422333)
                           , std::make_pair<uint32_t, uint64_t>(5, 15833292)
                           , std::make_pair<uint32_t, uint64_t>(6, 706045033)
                             ));

TEST_P(PerftPosition4, AtDepth)
{
    Position position(FenUtility::TEST4_FEN);

    const auto & [perftDepth, expectedResult] = GetParam();

    ASSERT_EQ(PerfomanceTester::perft(position, perftDepth), expectedResult);
}

#endif // TST_PERFTPOSITION4_H

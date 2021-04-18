#ifndef TST_PERFTPOSITION6_H
#define TST_PERFTPOSITION6_H

#include <gtest/gtest.h>

#include <Utility/Zobrist.h>
#include <BoardRepresentation/BB.h>
#include <BoardRepresentation/Position.h>
#include <Search/PerfomanceTester.h>

class PerftPosition6:
        public ::testing::TestWithParam<std::pair<uint32_t, uint64_t>>
{
public:
    static void SetUpTestSuite()
    {
        Zobrist::initializeTable();
        BB::initializeAll();
    }
};

INSTANTIATE_TEST_SUITE_P(Position6,
                         PerftPosition6,
                         ::testing::Values(
                             std::make_pair<uint32_t, uint64_t>(0, 1)
                           , std::make_pair<uint32_t, uint64_t>(1, 46)
                           , std::make_pair<uint32_t, uint64_t>(2, 2079)
                           , std::make_pair<uint32_t, uint64_t>(3, 89890)
                           , std::make_pair<uint32_t, uint64_t>(4, 3894594)
                           , std::make_pair<uint32_t, uint64_t>(5, 164075551)
                           , std::make_pair<uint32_t, uint64_t>(6, 6923051137)
                             ));

TEST_P(PerftPosition6, AtDepth)
{
    Position position(FenUtility::TEST6_FEN);

    const auto & [perftDepth, expectedResult] = GetParam();

    ASSERT_EQ(PerfomanceTester::perft(position, perftDepth), expectedResult);
}


#endif // TST_PERFTPOSITION6_H

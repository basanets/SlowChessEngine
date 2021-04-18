#ifndef TST_PERFTKIWIPETE_H
#define TST_PERFTKIWIPETE_H

#include <gtest/gtest.h>

#include <Utility/Zobrist.h>
#include <BoardRepresentation/BB.h>
#include <BoardRepresentation/Position.h>
#include <Search/PerfomanceTester.h>

class PerftKiwipete:
        public ::testing::TestWithParam<std::pair<uint32_t, uint64_t>>
{
public:
    static void SetUpTestSuite()
    {
        Zobrist::initializeTable();
        BB::initializeAll();
    }
};

INSTANTIATE_TEST_SUITE_P(Kiwipete,
                         PerftKiwipete,
                         ::testing::Values(
                             std::make_pair<uint32_t, uint64_t>(0, 1ull)
                           , std::make_pair<uint32_t, uint64_t>(1, 48ull)
                           , std::make_pair<uint32_t, uint64_t>(2, 2039ull)
                           , std::make_pair<uint32_t, uint64_t>(3, 97862ull)
                           , std::make_pair<uint32_t, uint64_t>(4, 4085603ull)
                           , std::make_pair<uint32_t, uint64_t>(5, 193690690ull)
                           , std::make_pair<uint32_t, uint64_t>(6, 8031647685ull)
                             ));

TEST_P(PerftKiwipete, AtDepth)
{
    Position position(FenUtility::KIWIPETE_FEN);

    const auto & [perftDepth, expectedResult] = GetParam();

    ASSERT_EQ(PerfomanceTester::perft(position, perftDepth), expectedResult);
}

#endif // TST_PERFTKIWIPETE_H

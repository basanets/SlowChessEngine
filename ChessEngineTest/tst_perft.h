#ifndef TST_PERFT_H
#define TST_PERFT_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include <Utility/Zobrist.h>
#include <BoardRepresentation/BB.h>

#include <BoardRepresentation/Position.h>
#include <Search/PerfomanceTester.h>

using namespace testing;

class Perft: public ::testing::Test
{
protected:
    static void SetUpTestSuite()
    {
        Zobrist::initializeTable();
        BB::initializeAll();
    }
};

TEST_F(Perft, StartingPosition)
{
    Position position(FenUtility::DEFAULT_FEN);

    ASSERT_EQ(PerfomanceTester::perft(position, 0), 1);
    ASSERT_EQ(PerfomanceTester::perft(position, 1), 20);
    ASSERT_EQ(PerfomanceTester::perft(position, 2), 400);
    ASSERT_EQ(PerfomanceTester::perft(position, 3), 8902);
    ASSERT_EQ(PerfomanceTester::perft(position, 4), 197281);
    ASSERT_EQ(PerfomanceTester::perft(position, 5), 4865609);
    ASSERT_EQ(PerfomanceTester::perft(position, 6), 119060324);
//    ASSERT_EQ(PerfomanceTester::perft(position, 7), 3195901860);
}

TEST_F(Perft, Kiwipete)
{
    Position position(FenUtility::KIWIPETE_FEN);

    ASSERT_EQ(PerfomanceTester::perft(position, 0), 1);
    ASSERT_EQ(PerfomanceTester::perft(position, 1), 48);
    ASSERT_EQ(PerfomanceTester::perft(position, 2), 2039);
    ASSERT_EQ(PerfomanceTester::perft(position, 3), 97862);
    ASSERT_EQ(PerfomanceTester::perft(position, 4), 4085603);
    ASSERT_EQ(PerfomanceTester::perft(position, 5), 193690690);
//    ASSERT_EQ(PerfomanceTester::perft(position, 6), 8031647685);
}

TEST_F(Perft, TestingPosition3)
{
    Position position(FenUtility::TEST3_FEN);

    ASSERT_EQ(PerfomanceTester::perft(position, 0), 1);
    ASSERT_EQ(PerfomanceTester::perft(position, 1), 14);
    ASSERT_EQ(PerfomanceTester::perft(position, 2), 191);
    ASSERT_EQ(PerfomanceTester::perft(position, 3), 2812);
    ASSERT_EQ(PerfomanceTester::perft(position, 4), 43238);
    ASSERT_EQ(PerfomanceTester::perft(position, 5), 674624);
    ASSERT_EQ(PerfomanceTester::perft(position, 6), 11030083);
    ASSERT_EQ(PerfomanceTester::perft(position, 7), 178633661);
//    ASSERT_EQ(PerfomanceTester::perft(position, 8), 3009794393);
}

TEST_F(Perft, TestingPosition4)
{
    Position position(FenUtility::TEST4_FEN);

    ASSERT_EQ(PerfomanceTester::perft(position, 0), 1);
    ASSERT_EQ(PerfomanceTester::perft(position, 1), 6);
    ASSERT_EQ(PerfomanceTester::perft(position, 2), 264);
    ASSERT_EQ(PerfomanceTester::perft(position, 3), 9467);
    ASSERT_EQ(PerfomanceTester::perft(position, 4), 422333);
    ASSERT_EQ(PerfomanceTester::perft(position, 5), 15833292);
//    ASSERT_EQ(PerfomanceTester::perft(position, 6), 706045033);
}

TEST_F(Perft, TestingPosition5)
{
    Position position(FenUtility::TEST5_FEN);

    ASSERT_EQ(PerfomanceTester::perft(position, 0), 1);
    ASSERT_EQ(PerfomanceTester::perft(position, 1), 44);
    ASSERT_EQ(PerfomanceTester::perft(position, 2), 1486);
    ASSERT_EQ(PerfomanceTester::perft(position, 3), 62379);
    ASSERT_EQ(PerfomanceTester::perft(position, 4), 2103487);
    ASSERT_EQ(PerfomanceTester::perft(position, 5), 89941194);
}

TEST_F(Perft, TestingPosition6)
{
    Position position(FenUtility::TEST6_FEN);

    ASSERT_EQ(PerfomanceTester::perft(position, 0), 1);
    ASSERT_EQ(PerfomanceTester::perft(position, 1), 46);
    ASSERT_EQ(PerfomanceTester::perft(position, 2), 2079);
    ASSERT_EQ(PerfomanceTester::perft(position, 3), 89890);
    ASSERT_EQ(PerfomanceTester::perft(position, 4), 3894594);
    ASSERT_EQ(PerfomanceTester::perft(position, 5), 164075551);
//    ASSERT_EQ(PerfomanceTester::perft(position, 6), 6923051137);
}

#endif // TST_PERFT_H

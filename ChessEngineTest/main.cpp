#include "Perft/tst_PerftStartingPosition.h"
#include "Perft/tst_PerftKiwipete.h"
#include "Perft/tst_PerftPosition3.h"
#include "Perft/tst_PerftPosition4.h"
#include "Perft/tst_PerftPosition5.h"
#include "Perft/tst_PerftPosition6.h"
#include <gtest/gtest.h>

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

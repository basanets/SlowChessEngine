cmake_minimum_required(VERSION 3.19)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(ChessEngineTest LANGUAGES CXX)

add_definitions(-DGTEST_LANGUAGE_CXX11)

find_package(Threads REQUIRED)

set(GOOGLETEST_DIR /usr/src/googletest)
set(GTestSrc ${GOOGLETEST_DIR}/googletest)
set(GMockSrc ${GOOGLETEST_DIR}/googlemock)

set(GTestFiles ${GTestSrc}/src/gtest-all.cc)
set(GTestIncludes ${GTestSrc} ${GTestSrc}/include)
if (NOT ${GMockSrc} STREQUAL "")
    list(APPEND GTestFiles ${GMockSrc}/src/gmock-all.cc)
    list(APPEND GTestIncludes ${GMockSrc} ${GMockSrc}/include)
endif ()

include_directories(${GTestIncludes})

add_executable(ChessEngineTest
    main.cpp
    tst_perft.h
    tst_PerftStartingPosition.h
               ${GTestFiles})
add_test(NAME perft COMMAND perft)

target_link_libraries(ChessEngineTest PRIVATE Threads::Threads)
target_link_libraries(ChessEngineTest PRIVATE ChessEngineCore)
target_include_directories(ChessEngineTest PRIVATE ../ChessEngineCore)


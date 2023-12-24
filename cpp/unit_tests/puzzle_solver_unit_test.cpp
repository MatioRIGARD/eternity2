#if UNIT_TEST_MODE

#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <algorithm>

#include "core/config.h"
#include "core/puzzle_manager.h"


// Puzzle solver basic algo
TEST(PuzzleSolver, BasicAlgorithm) {
    auto puzzleManager = PuzzleManager();

    puzzleManager.loadFromJsonFile(PUZZLE_VERY_EASY_DATA_FILE_PATH);
    puzzleManager.solve(PuzzleSolver::ALGORITHM_BASIC_BRUTE_FORCE);

}

// Puzzle solver basic algo
TEST(PuzzleSolver, FrameOnly) {
    auto puzzleManager = PuzzleManager();

    puzzleManager.loadFromJsonFile(PUZZLE_VERY_EASY_DATA_FILE_PATH);
    puzzleManager.solve(PuzzleSolver::ALGORITHM_ONLY_FRAME);
}

#endif  // UNIT_TEST_MODE

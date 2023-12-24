#if UNIT_TEST_MODE

#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <algorithm>

#include "core/config.h"
#include "core/puzzle_manager.h"


// Validate the puzzle pieces are in place
TEST(PuzzleSolver, PuzzleValidation) {
    auto puzzleManager = PuzzleManager();

    puzzleManager.loadFromJsonFile(PUZZLE_VERY_EASY_DATA_FILE_PATH);
}

// Get all conflict between pieces
TEST(PuzzleSolver, GetPuzzlePiecesConflicts) {
    auto puzzleManager = PuzzleManager();

    puzzleManager.loadFromJsonFile(PUZZLE_VERY_EASY_DATA_FILE_PATH);
}

// Puzzle solver basic algo
TEST(PuzzleSolver, BasicAlgorithm) {
    auto puzzleManager = PuzzleManager();

    puzzleManager.loadFromJsonFile(PUZZLE_VERY_EASY_DATA_FILE_PATH);
    // puzzleManager.solve(PuzzleSolver::ALGORITHM_BASIC_BRUTE_FORCE);
}

// Puzzle solver basic algo frame
TEST(PuzzleSolver, FrameOnly) {
    auto puzzleManager = PuzzleManager();

    puzzleManager.loadFromJsonFile(PUZZLE_VERY_EASY_DATA_FILE_PATH);
    // puzzleManager.solve(PuzzleSolver::ALGORITHM_ONLY_FRAME);
}

#endif  // UNIT_TEST_MODE

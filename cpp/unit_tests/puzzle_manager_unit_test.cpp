#if UNIT_TEST_MODE

#include "core/config.h"
#include "core/puzzle.h"
#include "core/puzzle_manager.h"

#include "core/puzzle_logger.h"

#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <algorithm>



// Puzzle file load
TEST(PuzzleManager, LoadDummyPuzzleFile) {
    auto puzzleManager = PuzzleManager();

    puzzleManager.loadFromJsonFile(PUZZLE_DUMMY_DATA_FILE_PATH);

    std::vector<PuzzlePiece> puzzlePieces = puzzleManager.getPuzzleAllPieces();
    EXPECT_NE(puzzlePieces.size(), 0) << "Vector is empty but expected not empty";

    for(auto piece: puzzlePieces) {
        for(int i=0; i<4; i++) {
            EXPECT_EQ(piece.m_colors[i], PIECE_COLOR_BORDER) << "Color differ for piece n." << static_cast<int>(piece.m_number) << " for color n." << i+1;
        }
    }
}

// check if loads also another file
TEST(PuzzleManager, LoadVeryEasyPuzzleFile) {
    auto puzzleManager = PuzzleManager();

    PuzzlePiece puzzlePieceExpected[5] = {
        {.m_number=0, .m_positionX=0, .m_positionY=0, .m_orientation=PIECE_ORIENTATION_NONE, .m_colors={PIECE_COLOR_PINK_YELLOW_SQUARE, PIECE_COLOR_ORANGE_LIGHT_BLUE_CROSS, PIECE_COLOR_BORDER, PIECE_COLOR_BORDER}},
        {.m_number=0, .m_positionX=0, .m_positionY=0, .m_orientation=PIECE_ORIENTATION_NONE, .m_colors={PIECE_COLOR_ORANGE_LIGHT_BLUE_CROSS, PIECE_COLOR_PINK_YELLOW_SQUARE, PIECE_COLOR_BORDER, PIECE_COLOR_BORDER}},
        {.m_number=0, .m_positionX=0, .m_positionY=0, .m_orientation=PIECE_ORIENTATION_NONE, .m_colors={PIECE_COLOR_ORANGE_LIGHT_BLUE_CROSS, PIECE_COLOR_PINK_YELLOW_SQUARE, PIECE_COLOR_BORDER, PIECE_COLOR_PINK_YELLOW_SQUARE}},
        {.m_number=0, .m_positionX=0, .m_positionY=0, .m_orientation=PIECE_ORIENTATION_NONE, .m_colors={PIECE_COLOR_PINK_YELLOW_SQUARE, PIECE_COLOR_ORANGE_LIGHT_BLUE_CROSS, PIECE_COLOR_BORDER, PIECE_COLOR_ORANGE_LIGHT_BLUE_CROSS}},
        {.m_number=0, .m_positionX=0, .m_positionY=0, .m_orientation=PIECE_ORIENTATION_NONE, .m_colors={PIECE_COLOR_ORANGE_LIGHT_BLUE_CROSS, PIECE_COLOR_PINK_YELLOW_SQUARE, PIECE_COLOR_ORANGE_LIGHT_BLUE_CROSS, PIECE_COLOR_PINK_YELLOW_SQUARE}}
    };

    puzzleManager.loadFromJsonFile(PUZZLE_VERY_EASY_DATA_FILE_PATH);

    std::vector<PuzzlePiece> puzzlePieces = puzzleManager.getPuzzleAllPieces();
    EXPECT_NE(puzzlePieces.size(), 0) << "Vector is empty but expected not empty";

    int pieceNumber = 0;
    int puzzlePieceExpectedNumber = 0;

    for(auto piece: puzzlePieces) {

        if(pieceNumber == 2) puzzlePieceExpectedNumber++;
        if(pieceNumber == 4) puzzlePieceExpectedNumber++;
        if(pieceNumber == 32) puzzlePieceExpectedNumber++;
        if(pieceNumber == 60) puzzlePieceExpectedNumber++;

        for(int colorNumber=0; colorNumber<4; colorNumber++) {
            EXPECT_EQ(piece.m_colors[colorNumber], puzzlePieceExpected[puzzlePieceExpectedNumber].m_colors[colorNumber]) << "Color differ for piece n." << static_cast<int>(piece.m_number) << " with color n." << colorNumber+1;
        }
        pieceNumber++;
    }
}

// test the PuzzleManager::getPiecesWithColor function
TEST(PuzzleManager, GetPiecesWithColor) {
    auto puzzleManager = PuzzleManager();

    puzzleManager.loadFromJsonFile(PUZZLE_VERY_EASY_DATA_FILE_PATH);

    std::vector<PuzzlePiece> borderPieces = puzzleManager.getPiecesWithColor(PIECE_COLOR_BORDER);
    EXPECT_NE(borderPieces.size(), 0) << "Vector is empty but expected not empty";

    for(auto piece: borderPieces) {
        int borderQty = 0;
        for(auto color: piece.m_colors) {
            if(color == PIECE_COLOR_BORDER) borderQty++;
        }
        EXPECT_GT(borderQty, 0)  << "The piece n." << static_cast<int>(piece.m_number) << " does not contain a border as it should";
    }
    EXPECT_EQ(borderPieces.size(), 60) << "In loaded puzzle, expected 60 border pieces but got " << borderPieces.size() << " pieces instead";
#if UNIT_TEST_ADDITIONNAL_LOGS
    PuzzleLogger::printPiecesInfos(borderPieces);
#endif
}

// test the setBasicPuzzlePiecesPlacement method
TEST(PuzzleManager, SetBasicPuzzlePiecesPlacement) {
    auto puzzleManager = PuzzleManager();

    puzzleManager.loadFromJsonFile(PUZZLE_DUMMY_DATA_FILE_PATH);
    puzzleManager.setBasicPuzzlePiecesPlacement();

    auto puzzlePieces = puzzleManager.getPuzzleAllPieces();

    for(int i=0; i<PIECES_QUANTITY; i++) {
        EXPECT_EQ(puzzlePieces[i].m_number, i) << "Expected the " << i+1 << "th piece to be the piece n." << i+1 << "but is the piece n." << static_cast<int>(puzzlePieces[i].m_number);
    }
#if UNIT_TEST_ADDITIONNAL_LOGS
    PuzzleLogger::printPuzzleRaw(puzzlePieces);
#endif
}

// test the PuzzleManager::getPiecesWithTwoAdjacentIdenticalColors function
TEST(PuzzleManager, GetPiecesWithTwoAdjacentIdenticalColors) {
    auto puzzleManager = PuzzleManager();

    puzzleManager.loadFromJsonFile(PUZZLE_ETERNITY_2_DATA_FILE_PATH);

    auto puzzlePieces = puzzleManager.getPiecesWithTwoAdjacentIdenticalColors();
    EXPECT_NE(puzzlePieces.size(), 0) << "Vector is empty but expected not empty";

    bool hasTwoAdjacentIdenticalColors = false;

    for(auto piece: puzzlePieces) {
        if(piece.m_colors[0] == piece.m_colors[1] ||
            piece.m_colors[1] == piece.m_colors[2] ||
            piece.m_colors[2] == piece.m_colors[3] ||
            piece.m_colors[3] == piece.m_colors[0]) hasTwoAdjacentIdenticalColors = true;
        else hasTwoAdjacentIdenticalColors = false;
        EXPECT_EQ(hasTwoAdjacentIdenticalColors, true) << "Piece n." << static_cast<int>(piece.m_number) << " doesn't contains at least 2 ajacent identical colors";
    }

#if UNIT_TEST_ADDITIONNAL_LOGS
    PuzzleLogger::printPiecesInfos(puzzlePieces);
#endif
}

TEST(PuzzleManager, GetPiecesWithTwoOpositeIdenticalColors) {
    auto puzzleManager = PuzzleManager();

    puzzleManager.loadFromJsonFile(PUZZLE_ETERNITY_2_DATA_FILE_PATH);

    auto puzzlePieces = puzzleManager.getPiecesWithTwoOppositeIdenticalColors();
    EXPECT_NE(puzzlePieces.size(), 0) << "Vector is empty but expected not empty";

    bool hasTwoOppositeIdenticalColors = false;

    for(auto piece: puzzlePieces) {

        if(piece.m_colors[0] == piece.m_colors[2] ||
            piece.m_colors[1] == piece.m_colors[3]) hasTwoOppositeIdenticalColors = true;
        else hasTwoOppositeIdenticalColors = false;

        EXPECT_EQ(hasTwoOppositeIdenticalColors, true) << "Piece n." << static_cast<int>(piece.m_number) << " doesn't contains at least 2 opposite identical colors";
    }

#if UNIT_TEST_ADDITIONNAL_LOGS
    PuzzleLogger::printPiecesInfos(puzzlePieces);
#endif
}

TEST(PuzzleManager, GetPiecesWithThreeIdenticalColors) {
    auto puzzleManager = PuzzleManager();

    puzzleManager.loadFromJsonFile(PUZZLE_ETERNITY_2_DATA_FILE_PATH);

    auto puzzlePieces = puzzleManager.getPiecesWithThreeIdenticalColors();
    EXPECT_NE(puzzlePieces.size(), 0) << "Vector is empty but expected not empty";

    bool hasThreeIdenticalColors = false;

    for(auto piece: puzzlePieces) {

        if((piece.m_colors[0] == piece.m_colors[1] && piece.m_colors[1] == piece.m_colors[2]) ||
            (piece.m_colors[1] == piece.m_colors[2] && piece.m_colors[2] == piece.m_colors[3]) ||
            (piece.m_colors[2] == piece.m_colors[3] && piece.m_colors[3] == piece.m_colors[0]) ||
            (piece.m_colors[3] == piece.m_colors[0] && piece.m_colors[0] == piece.m_colors[1])) hasThreeIdenticalColors = true;
        else hasThreeIdenticalColors = false;

        EXPECT_EQ(hasThreeIdenticalColors, true) << "Piece n." << static_cast<int>(piece.m_number) << " doesn't contains at least 3 identical colors";
    }

#if UNIT_TEST_ADDITIONNAL_LOGS
    PuzzleLogger::printPiecesInfos(puzzlePieces);
#endif
}

TEST(PuzzleManager, GetPiecesWithTwoIdenticalColors) {
    auto puzzleManager = PuzzleManager();

    puzzleManager.loadFromJsonFile(PUZZLE_ETERNITY_2_DATA_FILE_PATH);

    auto puzzlePieces = puzzleManager.getPiecesWithTwoIdenticalColors();
    EXPECT_NE(puzzlePieces.size(), 0) << "Vector is empty but expected not empty";

    bool hasTwoIdenticalColors = false;

    for(auto piece: puzzlePieces) {

        if(piece.m_colors[0] == piece.m_colors[1] ||
            piece.m_colors[1] == piece.m_colors[2] ||
            piece.m_colors[2] == piece.m_colors[3] ||
            piece.m_colors[3] == piece.m_colors[0] ||
            piece.m_colors[0] == piece.m_colors[2] ||
            piece.m_colors[1] == piece.m_colors[3]) hasTwoIdenticalColors = true;
        else hasTwoIdenticalColors = false;

        EXPECT_EQ(hasTwoIdenticalColors, true) << "Piece n." << static_cast<int>(piece.m_number) << " doesn't contains at least 2 identical colors";
    }

#if UNIT_TEST_ADDITIONNAL_LOGS
    PuzzleLogger::printPiecesInfos(puzzlePieces);
#endif
}

// just try to print info and log file, not a real test
TEST(PuzzleManager, PrintInfos) {
    auto puzzleManager = PuzzleManager();

    puzzleManager.loadFromJsonFile(PUZZLE_ETERNITY_2_DATA_FILE_PATH);
    puzzleManager.setBasicPuzzlePiecesPlacement();

    PuzzleLogger::writeInLogFilePuzzleInfos(puzzleManager);
    PuzzleLogger::writeInLogFilePuzzleRaw(puzzleManager);
}


#endif  // UNIT_TEST_MODE

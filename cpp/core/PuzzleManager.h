#ifndef PUZZLE_MANAGER_H
#define PUZZLE_MANAGER_H

#include "core/Puzzle.h"
#include "core/PuzzleSolver.h"
#include <string>
#include <vector>
#include <map>

class PuzzleManager {

private:
    PuzzlePiece m_puzzlePieces[256];
    PuzzleSolver m_solver;

public:
    PuzzleManager();
    ~PuzzleManager();

    int loadFromJsonFile(std::string path);

    static std::vector<PuzzlePiece> getPiecesWithColor(std::vector<PuzzlePiece> piecesList, PieceColor color);
    std::vector<PuzzlePiece> getPiecesWithColor(PieceColor color);
    std::vector<PuzzlePiece> getPiecesWithTwoAdjacentIdenticalColors();
    std::vector<PuzzlePiece> getPiecesWithTwoOppositeIdenticalColors();
    std::vector<PuzzlePiece> getPiecesWithThreeIdenticalColors();
    std::vector<PuzzlePiece> getPiecesWithTwoIdenticalColors();
    std::vector<PuzzlePiece> getPuzzleAllPieces();

    void setBasicPuzzlePiecesPlacement();

    static inline std::map<std::string, PieceColor> pieceColorMap = {
        {"BORDER", PIECE_COLOR_BORDER},
        {"ORANGE_LIGHT_BLUE_CROSS", PIECE_COLOR_ORANGE_LIGHT_BLUE_CROSS},
        {"PINK_YELLOW_CROSS", PIECE_COLOR_PINK_YELLOW_CROSS},
        {"VIOLET_GREEN_CIRCLE", PIECE_COLOR_VIOLET_GREEN_CIRCLE},
        {"LIGHT_BLUE_PINK_CROSS", PIECE_COLOR_LIGHT_BLUE_PINK_CROSS},
        {"GREEN_BLUE_CIRCLE", PIECE_COLOR_GREEN_BLUE_CIRCLE},
        {"VIOLET_YELLOW_CIRCLE", PIECE_COLOR_VIOLET_YELLOW_CIRCLE},
        {"LIGHT_BLUE_PINK_SQUARE", PIECE_COLOR_LIGHT_BLUE_PINK_SQUARE},
        {"BLUE_ORANGE_CROSS", PIECE_COLOR_BLUE_ORANGE_CROSS},
        {"BLUE_YELLOW_FLOWER", PIECE_COLOR_BLUE_YELLOW_FLOWER},
        {"VIOLET_LIGHT_BLUE_CROSS", PIECE_COLOR_VIOLET_LIGHT_BLUE_CROSS},
        {"GREEN_ORANGE_CROSS", PIECE_COLOR_GREEN_ORANGE_CROSS},
        {"YELLOW_BLUE_SQUARE", PIECE_COLOR_YELLOW_BLUE_SQUARE},
        {"RED_ORANGE_HOLLOW_SQUARE", PIECE_COLOR_RED_ORANGE_HOLLOW_SQUARE},
        {"GREEN_PINK_CROSS", PIECE_COLOR_GREEN_PINK_CROSS},
        {"YELLOW_GREEN_HOLLOW_SQUARE", PIECE_COLOR_YELLOW_GREEN_HOLLOW_SQUARE},
        {"BLUE_LIGHT_BLUE_HOLLOW_SQUARE", PIECE_COLOR_BLUE_LIGHT_BLUE_HOLLOW_SQUARE},
        {"PINK_LIGHT_BLUE_HOLLOW_FLOWER", PIECE_COLOR_PINK_LIGHT_BLUE_HOLLOW_FLOWER},
        {"YELLOW_LIGHT_BLUE_STAR", PIECE_COLOR_YELLOW_LIGHT_BLUE_STAR},
        {"VIOLET_YELLOW_STAR", PIECE_COLOR_VIOLET_YELLOW_STAR},
        {"ORANGE_VIOLET_STAR", PIECE_COLOR_ORANGE_VIOLET_STAR},
        {"PINK_YELLOW_SQUARE", PIECE_COLOR_PINK_YELLOW_SQUARE},
        {"BLUE_PINK_CIRCLE", PIECE_COLOR_BLUE_PINK_CIRCLE}
    };
};



#endif  // PUZZLE_MANAGER_H

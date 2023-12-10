#ifndef PUZZLE_LOGGER_H
#define PUZZLE_LOGGER_H

#include "core/Puzzle.h"
#include "core/PuzzleManager.h"
#include "core/config.h"
#include <vector>
#include <iostream>

class PuzzleLogger {

public:
    static std::string getPuzzleRaw(std::vector<PuzzlePiece> pieces);
    static std::string getPiecesInfos(std::vector<PuzzlePiece> pieces);
    static std::string getPuzzleInfos(PuzzleManager &PuzzleManager);

    static void printPuzzleRaw(std::vector<PuzzlePiece> pieces);
    static void printPiecesInfos(std::vector<PuzzlePiece> pieces);
    static void printPuzzleInfos(PuzzleManager &PuzzleManager);

    static void writeInLogFilePuzzleInfos(PuzzleManager &PuzzleManager, std::string logFilePath=PUZZLE_INFOS_LOG_FILE_PATH);
    static void writeInLogFilePuzzleRaw(PuzzleManager &PuzzleManager, std::string logFilePath=PUZZLE_RAW_LOG_FILE_PATH);
};

#endif  // PUZZLE_LOGGER_H

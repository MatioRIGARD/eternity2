#include "core/PuzzleLogger.h"
#include <iomanip>
#include <sstream>
#include <fstream>


std::string PuzzleLogger::getPuzzleRaw(std::vector<PuzzlePiece> pieces) {
    std::stringstream puzzleRaw;
    puzzleRaw << "Current Puzzle looks like this (number/orientation):" << std::endl;

    PuzzlePiece puzzlePieces[PIECES_QUANTITY];

    // reset values
    for(auto i=0; i<PIECES_QUANTITY; i++) {
        puzzlePieces[i].m_number = 0;
        puzzlePieces[i].m_orientation = PIECE_ORIENTATION_NONE;
        puzzlePieces[i].m_colors[0] = PIECE_COLOR_NONE;
        puzzlePieces[i].m_colors[1] = PIECE_COLOR_NONE;
        puzzlePieces[i].m_colors[2] = PIECE_COLOR_NONE;
        puzzlePieces[i].m_colors[3] = PIECE_COLOR_NONE;
    }

    for(auto i=0; i<PIECES_QUANTITY; i++) {
        auto currentPiecePosition = (pieces[i].m_positionY*PUZZLE_Y_DIMENSION)+pieces[i].m_positionX;
        puzzlePieces[currentPiecePosition] = pieces[i];
    }

    // print
    for(auto i=0; i<PIECES_QUANTITY; i++) {
        puzzleRaw << std::setfill('0') << std::setw(3) << static_cast<int>(puzzlePieces[i].m_number+1) << "/";
        puzzleRaw << std::setfill('0') << std::setw(1) << static_cast<int>(puzzlePieces[i].m_orientation) << " ";
        if((i+1)%16 == 0) puzzleRaw << std::endl;
    }
    return puzzleRaw.str();
}

std::string PuzzleLogger::getPiecesInfos(std::vector<PuzzlePiece> pieces) {
    std::stringstream piecesInfos;

    for(auto piece: pieces) {
        piecesInfos << "Piece n." << static_cast<int>(piece.m_number+1) << ":" << std::endl;
        piecesInfos << "    --> colors: " << static_cast<int>(piece.m_colors[0]) << ", ";
        piecesInfos << static_cast<int>(piece.m_colors[1]) << ", ";
        piecesInfos << static_cast<int>(piece.m_colors[2]) << ", ";
        piecesInfos << static_cast<int>(piece.m_colors[3]) << std::endl;
        piecesInfos << "    --> orientation: " << static_cast<int>(piece.m_orientation) << std::endl;
        piecesInfos << "    --> positionXY: (" << static_cast<int>(piece.m_positionX) << ";" << static_cast<int>(piece.m_positionY) << ")" << std::endl;
    }
    return piecesInfos.str();
}

std::string PuzzleLogger::getPuzzleInfos(PuzzleManager &puzzleManager) {
    std::stringstream puzzleInfos;

    puzzleInfos << std::endl << "Puzzle pieces list:" << std::endl << std::endl;

    auto puzzleAllPieces = puzzleManager.getPuzzleAllPieces();

    puzzleInfos << PuzzleLogger::getPiecesInfos(puzzleAllPieces);

    puzzleInfos << std::endl << "==============================================" << std::endl;

    puzzleInfos << std::endl << "Pieces by color:" << std::endl << std::endl;
    for(int color=PIECE_COLOR_BORDER; color<PIECE_COLOR_BLUE_PINK_CIRCLE; color++) {
        auto piecesWithColor = puzzleManager.getPiecesWithColor(static_cast<PieceColor>(color));
        puzzleInfos << std::endl << "----------------------------------------------" << std::endl;
        puzzleInfos << std::endl << "For color n." << color << " (" << piecesWithColor.size() << " pieces):" << std::endl << std::endl;
        puzzleInfos << PuzzleLogger::getPiecesInfos(piecesWithColor);
    }

    puzzleInfos << std::endl << "==============================================" << std::endl;

    auto piecesWithTwoAdjacentIdenticalColors = puzzleManager.getPiecesWithTwoAdjacentIdenticalColors();
    puzzleInfos << std::endl << "Pieces with 2 adjacent identical colors ("<< piecesWithTwoAdjacentIdenticalColors.size() <<" pieces):" << std::endl << std::endl;
    puzzleInfos << PuzzleLogger::getPiecesInfos(piecesWithTwoAdjacentIdenticalColors);

    puzzleInfos << std::endl << "==============================================" << std::endl;

    auto piecesWithTwoOppositeIdenticalColors = puzzleManager.getPiecesWithTwoOppositeIdenticalColors();
    puzzleInfos << std::endl << "Pieces with 2 opposite identical colors (" << piecesWithTwoOppositeIdenticalColors.size() << " pieces):" << std::endl << std::endl;
    puzzleInfos << PuzzleLogger::getPiecesInfos(piecesWithTwoOppositeIdenticalColors);

    puzzleInfos << std::endl << "==============================================" << std::endl;

    auto piecesWithThreeIdenticalColors = puzzleManager.getPiecesWithThreeIdenticalColors();
    puzzleInfos << std::endl << "Pieces with 3 identical colors (" << piecesWithThreeIdenticalColors.size() << " pieces):" << std::endl << std::endl;
    puzzleInfos << PuzzleLogger::getPiecesInfos(piecesWithThreeIdenticalColors);

    puzzleInfos << std::endl << "==============================================" << std::endl;

    auto piecesWithTwoIdenticalColors = puzzleManager.getPiecesWithTwoIdenticalColors();
    puzzleInfos << std::endl << "Pieces with 2 identical colors (" << piecesWithTwoIdenticalColors.size() << " pieces):" << std::endl << std::endl;
    puzzleInfos << PuzzleLogger::getPiecesInfos(piecesWithTwoIdenticalColors);

    puzzleInfos << std::endl << "==============================================" << std::endl;

    puzzleInfos << std::endl << "Puzzle raw (" << puzzleAllPieces.size() << " pieces):" << std::endl << std::endl;
    puzzleInfos << PuzzleLogger::getPuzzleRaw(puzzleAllPieces);

    return puzzleInfos.str();
}

void PuzzleLogger::printPuzzleRaw(std::vector<PuzzlePiece> pieces) {
    std::cout << PuzzleLogger::getPuzzleRaw(pieces);
}

void PuzzleLogger::printPiecesInfos(std::vector<PuzzlePiece> pieces) {
    std::cout << PuzzleLogger::getPiecesInfos(pieces);
}

void PuzzleLogger::printPuzzleInfos(PuzzleManager &puzzleManager) {
    std::cout << PuzzleLogger::getPuzzleInfos(puzzleManager);
}

void PuzzleLogger::writeInLogFilePuzzleInfos(PuzzleManager &puzzleManager, std::string logFilePath) {

    std::ofstream logFile(logFilePath);

    if (!logFile.is_open()) {
        std::cerr << "Error: Can't open file " << logFilePath << std::endl;
        exit(1);
    }
    logFile << PuzzleLogger::getPuzzleInfos(puzzleManager);

    if (!logFile) {
        std::cerr << "Error: While writting in file " << logFilePath << std::endl;
        exit(1);
    }
    logFile.close(); // Fermeture du fichier
}

void PuzzleLogger::writeInLogFilePuzzleRaw(PuzzleManager &puzzleManager, std::string logFilePath) {

    std::ofstream logFile(logFilePath);

    if (!logFile.is_open()) {
        std::cerr << "Error: Can't open file " << logFilePath << std::endl;
        exit(1);
    }
    logFile << PuzzleLogger::getPuzzleRaw(puzzleManager.getPuzzleAllPieces());

    if (!logFile) {
        std::cerr << "Error: While writting in file " << logFilePath << std::endl;
        exit(1);
    }
    logFile.close(); // Fermeture du fichier
}


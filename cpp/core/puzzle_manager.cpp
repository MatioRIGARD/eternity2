#include "core/puzzle_manager.h"
#include "core/config.h"
#include <boost/property_tree/json_parser.hpp>
#include <fstream>
#include <iostream>

PuzzleManager::PuzzleManager() {

    // pieces list
    for(auto i=0; i<PIECES_QUANTITY; i++) {
        this->m_puzzlePieces[i].m_number = 0;
        this->m_puzzlePieces[i].m_positionX = 0;
        this->m_puzzlePieces[i].m_positionY = 0;
        this->m_puzzlePieces[i].m_orientation = PIECE_ORIENTATION_NONE;
        this->m_puzzlePieces[i].m_colors[0] = PIECE_COLOR_NONE;
        this->m_puzzlePieces[i].m_colors[1] = PIECE_COLOR_NONE;
        this->m_puzzlePieces[i].m_colors[2] = PIECE_COLOR_NONE;
        this->m_puzzlePieces[i].m_colors[3] = PIECE_COLOR_NONE;
    }
};

PuzzleManager::~PuzzleManager() {

};

int PuzzleManager::loadFromJsonFile(std::string path) {
    boost::property_tree::ptree ptree;

    try {
        boost::property_tree::read_json(path, ptree);
    }
    catch (const boost::property_tree::json_parser::json_parser_error& e) {
        std::cerr << "Error reading or parsing JSON: " << e.what() << std::endl;
        exit(1);
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        exit(2);
    }

    auto piecesArray = ptree.get_child("pieces");
    int itemNumber = 0;
    int colorNumber = 0;

    // for all pieces
    for (const auto& line : piecesArray) {
        this->m_puzzlePieces[itemNumber].m_number = itemNumber;
        this->m_puzzlePieces[itemNumber].m_orientation = PIECE_ORIENTATION_NONE;

        // set colors
        for (const auto& subitem : line.second) {
            auto color = subitem.second.data();
            this->m_puzzlePieces[itemNumber].m_colors[colorNumber] = pieceColorMap[color];
            colorNumber++;
        }

        colorNumber = 0;
        itemNumber++;
    }

    return 0;
};

std::vector<PuzzlePiece> PuzzleManager::getPiecesWithColor(std::vector<PuzzlePiece> piecesList, PieceColor color) {
    std::vector<PuzzlePiece> returnPiecesList;

    bool containsColor = false;
    for(auto piece: piecesList) {
        containsColor = false;
        for(auto pieceColor: piece.m_colors) {
            if(pieceColor == color) containsColor = true;
        }
        if(containsColor) returnPiecesList.push_back(piece);
    }
    return returnPiecesList;
};

std::vector<PuzzlePiece> PuzzleManager::getPiecesWithColor(PieceColor color) {
    std::vector<PuzzlePiece> returnPiecesList;

    for(auto piece: this->m_puzzlePieces) {
        returnPiecesList.push_back(piece);
    }

    return PuzzleManager::getPiecesWithColor(returnPiecesList, color);
}

std::vector<PuzzlePiece> PuzzleManager::getPiecesWithTwoAdjacentIdenticalColors() {
    std::vector<PuzzlePiece> returnPiecesList;

    for(auto piece: this->m_puzzlePieces) {
        if(piece.m_colors[0] == piece.m_colors[1] ||
            piece.m_colors[1] == piece.m_colors[2] ||
            piece.m_colors[2] == piece.m_colors[3] ||
            piece.m_colors[3] == piece.m_colors[0]) returnPiecesList.push_back(piece);
    }

    return returnPiecesList;
};

std::vector<PuzzlePiece> PuzzleManager::getPiecesWithTwoOppositeIdenticalColors() {
    std::vector<PuzzlePiece> returnPiecesList;

    for(auto piece: this->m_puzzlePieces) {
        if(piece.m_colors[0] == piece.m_colors[2] ||
            piece.m_colors[1] == piece.m_colors[3]) returnPiecesList.push_back(piece);
    }

    return returnPiecesList;
};

std::vector<PuzzlePiece> PuzzleManager::getPiecesWithThreeIdenticalColors() {
    std::vector<PuzzlePiece> returnPiecesList;

    for(auto piece: this->m_puzzlePieces) {
        if((piece.m_colors[0] == piece.m_colors[1] && piece.m_colors[1] == piece.m_colors[2]) ||
            (piece.m_colors[1] == piece.m_colors[2] && piece.m_colors[2] == piece.m_colors[3]) ||
            (piece.m_colors[2] == piece.m_colors[3] && piece.m_colors[3] == piece.m_colors[0]) ||
            (piece.m_colors[3] == piece.m_colors[0] && piece.m_colors[0] == piece.m_colors[1])) returnPiecesList.push_back(piece);
    }

    return returnPiecesList;
};

std::vector<PuzzlePiece> PuzzleManager::getPiecesWithTwoIdenticalColors() {
    std::vector<PuzzlePiece> returnPiecesList;

    for(auto piece: this->m_puzzlePieces) {
        if(piece.m_colors[0] == piece.m_colors[1] ||
            piece.m_colors[1] == piece.m_colors[2] ||
            piece.m_colors[2] == piece.m_colors[3] ||
            piece.m_colors[3] == piece.m_colors[0] ||
            piece.m_colors[0] == piece.m_colors[2] ||
            piece.m_colors[1] == piece.m_colors[3]) returnPiecesList.push_back(piece);
    }

    return returnPiecesList;
};

std::vector<PuzzlePiece> PuzzleManager::getPuzzleAllPieces() {
    std::vector<PuzzlePiece> returnVector;

    for(auto piece: this->m_puzzlePieces) {
        returnVector.push_back(piece);
    }

    return returnVector;
}

void PuzzleManager::setBasicPuzzlePiecesPlacement() {

    for(int i=0; i<PIECES_QUANTITY; i++) {
        int positionY = i/PUZZLE_Y_DIMENSION;
        int positionX = i%PUZZLE_Y_DIMENSION;
        this->m_puzzlePieces[i].m_positionX = positionX;
        this->m_puzzlePieces[i].m_positionY = positionY;
    }
}

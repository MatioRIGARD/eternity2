#if !UNIT_TEST_MODE

#include <iostream>

#include "utils/args_parser.h"
#include "core/puzzle_manager.h"
#include "core/puzzle_logger.h"
#include "core/config.h"

using namespace std;

int main(int argc, char **argv) {

    std::cout << "Run solving soft..." << std::endl;

    ArgsParser argsParser;
    argsParser.parse(argc, argv);

    PuzzleManager puzzleManager;
    puzzleManager.loadFromJsonFile(PUZZLE_ETERNITY_2_DATA_FILE_PATH);

    if(std::get<bool>(argsParser.getOptionValue(ArgsParser::ARG_LOG_INFO)) == true) PuzzleLogger::writeInLogFilePuzzleInfos(puzzleManager);
    if(std::get<bool>(argsParser.getOptionValue(ArgsParser::ARG_LOG_PUZZLE_RAW)) == true) PuzzleLogger::writeInLogFilePuzzleRaw(puzzleManager);

    // will change by algo type enum later
    int algoNumber = 0;
    try {
        algoNumber = std::get<int>(argsParser.getOptionValue(ArgsParser::ARG_ALGO_NUMBER));
    }
    catch(const std::exception& e) {
        std::cout << "No algo specified, will use algo n." << int(algoNumber) << std::endl;
    }
    puzzleManager.solve(algoNumber);

    return 0;
}

#else

#include <gtest/gtest.h>

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}

#endif  // UNIT_TEST_MODE

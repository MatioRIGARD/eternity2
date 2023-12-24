#if UNIT_TEST_MODE==0

#include <iostream>

#include "utils/args_parser.h"

using namespace std;

int main(int argc, char **argv) {
    ArgsParser argsParser;
    argsParser.parse(argc, argv);

    argsParser.getOptionValue(ArgsParser::ARG_ALGO_NUMBER);

    return 0;
}

#elif UNIT_TEST_MODE==1

#include <gtest/gtest.h>

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

#endif  // UNIT_TEST_MODE

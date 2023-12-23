#if UNIT_TEST_MODE==1

#include <gtest/gtest.h>
#include <string>
#include "utils/args_parser.h"


// No args
TEST(ArgsParser, NoArgs) {
    const char* argv[] = {};
    int argc = sizeof(argv)/sizeof(char*);

    ArgsParser argsParser;
    argsParser.parse(argc, const_cast<char**>(argv));

    EXPECT_EQ(argsParser.getOptionValue(ArgsParser::ARG_ALGO_NUMBER), "false");
    EXPECT_EQ(argsParser.getOptionValue(ArgsParser::ARG_LOG_INFO), "false");
    EXPECT_EQ(argsParser.getOptionValue(ArgsParser::ARG_LOG_PUZZLE_RAW), "false");
    EXPECT_EQ(argsParser.getOptionValue(ArgsParser::ARG_RUN_UNIT_TEST), "false");
}

// Puzzle file load
TEST(ArgsParser, BasicArgsParsing) {
    const char* argv[] = {"--run_unit_test"};
    int argc = sizeof(argv)/sizeof(char*);

    ArgsParser argsParser;
    argsParser.parse(argc, const_cast<char**>(argv));

    EXPECT_EQ(argsParser.getOptionValue(ArgsParser::ARG_ALGO_NUMBER), "false");
    EXPECT_EQ(argsParser.getOptionValue(ArgsParser::ARG_LOG_INFO), "false");
    EXPECT_EQ(argsParser.getOptionValue(ArgsParser::ARG_LOG_PUZZLE_RAW), "false");
    EXPECT_EQ(argsParser.getOptionValue(ArgsParser::ARG_RUN_UNIT_TEST), "true");
}

// Arg with parameter
TEST(ArgsParser, ParameterArg) {
    const char* argv[] = {"--algo_number", "99"};
    int argc = sizeof(argv)/sizeof(char*);

    ArgsParser argsParser;
    argsParser.parse(argc, const_cast<char**>(argv));

    EXPECT_EQ(argsParser.getOptionValue(ArgsParser::ARG_ALGO_NUMBER), "99");
    EXPECT_EQ(argsParser.getOptionValue(ArgsParser::ARG_LOG_INFO), "false");
    EXPECT_EQ(argsParser.getOptionValue(ArgsParser::ARG_LOG_PUZZLE_RAW), "false");
    EXPECT_EQ(argsParser.getOptionValue(ArgsParser::ARG_RUN_UNIT_TEST), "false");
}

// All args (basic actual)
TEST(ArgsParser, AllArgs) {
    const char* argv[] = {"--run_unit_test", "--algo_number", "99", "--log_info", "--log_puzzle_raw"};
    int argc = sizeof(argv)/sizeof(char*);

    ArgsParser argsParser;
    argsParser.parse(argc, const_cast<char**>(argv));

    EXPECT_EQ(argsParser.getOptionValue(ArgsParser::ARG_ALGO_NUMBER), "99");
    EXPECT_EQ(argsParser.getOptionValue(ArgsParser::ARG_LOG_INFO), "true");
    EXPECT_EQ(argsParser.getOptionValue(ArgsParser::ARG_LOG_PUZZLE_RAW), "true");
    EXPECT_EQ(argsParser.getOptionValue(ArgsParser::ARG_RUN_UNIT_TEST), "true");
}


#endif  // UNIT_TEST_MODE

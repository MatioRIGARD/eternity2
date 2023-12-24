#if UNIT_TEST_MODE

#include <gtest/gtest.h>
#include <string>
#include "utils/args_parser.h"


// Try convert from variant to bool, to int, etc...
TEST(ArgsParser, TypeConversion) {
    ArgsParser argsParser;

    ArgsParser::variant boolVariant1 = "true";
    ArgsParser::variant boolVariant2 = "false";
    ArgsParser::variant intVariant = "93";
    ArgsParser::variant stringVariant1 = "";
    ArgsParser::variant stringVariant2 = "azeaze";

    EXPECT_EQ(std::get<bool>(argsParser.unitTestWrapper_tryGetConvertFromArgVariantToBool(boolVariant1)), true);
    EXPECT_EQ(std::get<bool>(argsParser.unitTestWrapper_tryGetConvertFromArgVariantToBool(boolVariant2)), false);
    EXPECT_EQ(std::get<std::string>(argsParser.unitTestWrapper_tryGetConvertFromArgVariantToBool(intVariant)), "93");
    EXPECT_EQ(std::get<std::string>(argsParser.unitTestWrapper_tryGetConvertFromArgVariantToBool(stringVariant1)), "");
    EXPECT_EQ(std::get<std::string>(argsParser.unitTestWrapper_tryGetConvertFromArgVariantToBool(stringVariant2)), "azeaze");

    EXPECT_EQ(std::get<std::string>(argsParser.unitTestWrapper_tryGetConvertFromArgVariantToInt(boolVariant1)), "true");
    EXPECT_EQ(std::get<std::string>(argsParser.unitTestWrapper_tryGetConvertFromArgVariantToInt(boolVariant2)), "false");
    EXPECT_EQ(std::get<int>(argsParser.unitTestWrapper_tryGetConvertFromArgVariantToInt(intVariant)), 93);
    EXPECT_EQ(std::get<std::string>(argsParser.unitTestWrapper_tryGetConvertFromArgVariantToInt(stringVariant1)), "");
    EXPECT_EQ(std::get<std::string>(argsParser.unitTestWrapper_tryGetConvertFromArgVariantToInt(stringVariant2)), "azeaze");

    EXPECT_EQ(std::get<bool>(argsParser.unitTestWrapper_getArgVariantRealType(boolVariant1)), true);
    EXPECT_EQ(std::get<bool>(argsParser.unitTestWrapper_getArgVariantRealType(boolVariant2)), false);
    EXPECT_EQ(std::get<int>(argsParser.unitTestWrapper_getArgVariantRealType(intVariant)), 93);
    EXPECT_EQ(std::get<std::string>(argsParser.unitTestWrapper_getArgVariantRealType(stringVariant1)), "");
    EXPECT_EQ(std::get<std::string>(argsParser.unitTestWrapper_getArgVariantRealType(stringVariant2)), "azeaze");
}

// No args
TEST(ArgsParser, NoArgs) {
    const char* argv[] = {};
    int argc = sizeof(argv)/sizeof(char*);

    ArgsParser argsParser;
    argsParser.parse(argc, const_cast<char**>(argv));

    EXPECT_FALSE(std::get<bool>(argsParser.getOptionValue(ArgsParser::ARG_ALGO_NUMBER)));
    EXPECT_FALSE(std::get<bool>(argsParser.getOptionValue(ArgsParser::ARG_LOG_INFO)));
    EXPECT_FALSE(std::get<bool>(argsParser.getOptionValue(ArgsParser::ARG_LOG_PUZZLE_RAW)));
}

// Puzzle file load
TEST(ArgsParser, BasicArgsParsing) {
    const char* argv[] = {"--log_info"};
    int argc = sizeof(argv)/sizeof(char*);

    ArgsParser argsParser;
    argsParser.parse(argc, const_cast<char**>(argv));

    EXPECT_FALSE(std::get<bool>(argsParser.getOptionValue(ArgsParser::ARG_ALGO_NUMBER)));
    EXPECT_TRUE(std::get<bool>(argsParser.getOptionValue(ArgsParser::ARG_LOG_INFO)));
    EXPECT_FALSE(std::get<bool>(argsParser.getOptionValue(ArgsParser::ARG_LOG_PUZZLE_RAW)));
}

// Arg with parameter
TEST(ArgsParser, ParameterArg) {
    const char* argv[] = {"--algo_number", "99"};
    int argc = sizeof(argv)/sizeof(char*);

    ArgsParser argsParser;
    argsParser.parse(argc, const_cast<char**>(argv));

    EXPECT_EQ(std::get<int>(argsParser.getOptionValue(ArgsParser::ARG_ALGO_NUMBER)), 99);
    EXPECT_FALSE(std::get<bool>(argsParser.getOptionValue(ArgsParser::ARG_LOG_INFO)));
    EXPECT_FALSE(std::get<bool>(argsParser.getOptionValue(ArgsParser::ARG_LOG_PUZZLE_RAW)));
}

// All args (basic actual)
TEST(ArgsParser, AllArgs) {
    const char* argv[] = {"--algo_number", "99", "--log_info", "--log_puzzle_raw"};
    int argc = sizeof(argv)/sizeof(char*);

    ArgsParser argsParser;
    argsParser.parse(argc, const_cast<char**>(argv));

    EXPECT_EQ(std::get<int>(argsParser.getOptionValue(ArgsParser::ARG_ALGO_NUMBER)), 99);
    EXPECT_TRUE(std::get<bool>(argsParser.getOptionValue(ArgsParser::ARG_LOG_INFO)));
    EXPECT_TRUE(std::get<bool>(argsParser.getOptionValue(ArgsParser::ARG_LOG_PUZZLE_RAW)));
}


#endif  // UNIT_TEST_MODE

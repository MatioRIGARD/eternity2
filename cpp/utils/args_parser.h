#ifndef ARGSPARSER_H
#define ARGSPARSER_H

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <variant>


class ArgsParser
{
public:

    typedef std::variant<bool, int, std::string> variant;

    enum ArgsAvailableE {
        ARG_ALGO_NUMBER,
        ARG_LOG_INFO,
        ARG_LOG_PUZZLE_RAW
    };
    const std::map<ArgsAvailableE, std::string> argsMap = {
        {ARG_ALGO_NUMBER, "algo_number"},
        {ARG_LOG_INFO, "log_info"},
        {ARG_LOG_PUZZLE_RAW, "log_puzzle_raw"}
    };

    ArgsParser();
    ~ArgsParser();

    void parse(int argc, char **argv);

    ArgsParser::variant getOptionValue(ArgsAvailableE optionName);
    std::string getArgsMapString(ArgsAvailableE optionName);


private:
    int rawArgc;
    std::vector<std::string> rawArgv;

    std::map<ArgsAvailableE, ArgsParser::variant> optionsValues;
    std::vector<ArgsAvailableE> enabledOptions;

    ArgsParser::variant tryGetConvertFromArgVariantToInt(ArgsParser::variant variant);
    ArgsParser::variant tryGetConvertFromArgVariantToBool(ArgsParser::variant variant);
    ArgsParser::variant getArgVariantRealType(ArgsParser::variant variant);


#if UNIT_TEST_MODE==1
public:
    ArgsParser::variant unitTestWrapper_tryGetConvertFromArgVariantToInt(ArgsParser::variant variant);
    ArgsParser::variant unitTestWrapper_tryGetConvertFromArgVariantToBool(ArgsParser::variant variant);
    ArgsParser::variant unitTestWrapper_getArgVariantRealType(ArgsParser::variant variant);
#endif  // UNIT_TEST_MODE
};

#endif  // ARGSPARSER_H


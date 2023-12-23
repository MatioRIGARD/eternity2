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

    enum ArgsAvailableE {
        ARG_RUN_UNIT_TEST,
        ARG_ALGO_NUMBER,
        ARG_LOG_INFO,
        ARG_LOG_PUZZLE_RAW
    };
    const std::map<ArgsAvailableE, std::string> argsMap = {
        {ARG_RUN_UNIT_TEST, "run_unit_test"},
        {ARG_ALGO_NUMBER, "algo_number"},
        {ARG_LOG_INFO, "log_info"},
        {ARG_LOG_PUZZLE_RAW, "log_puzzle_raw"}
    };

    ArgsParser();
    ~ArgsParser();

    void parse(int argc, char *argv[]);

    std::string getOptionValue(ArgsAvailableE optionName);

private:
    int rawArgc;
    std::vector<std::string> rawArgv;

    std::map<ArgsAvailableE, std::string> optionsValues;
    std::vector<ArgsAvailableE> enabledOptions;
};

#endif // ARGSPARSER_H


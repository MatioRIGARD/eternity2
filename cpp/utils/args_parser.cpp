#include "utils/args_parser.h"
#include <algorithm>

ArgsParser::ArgsParser() {

}

ArgsParser::~ArgsParser() {

}

void ArgsParser::parse(const int argc, char *argv[]) {
    this->rawArgc = argc;
    // add argv to class attribute
    for(int i=0; i<this->rawArgc; i++) {
        this->rawArgv.push_back(std::string(argv[i]));
    }

    // init option values with empty string for each element of argsMap
    for(auto& [key, value]: this->argsMap) {
        this->optionsValues[key] = "";
    }

    // for each rawArg
    for(int i=0; i<this->rawArgc; i++) {
        // is long option
        if(this->rawArgv[i].find("--") == 0) {
            //for each element of argsMap
            for(const auto& [key, value]: this->argsMap) {
                // removed "--" of current argv
                std::string model = std::string(this->rawArgv[i]).erase(0, 2);
                // check if string is current argsMap element iterated
                if(value == model) {
                    // enable option
                    this->enabledOptions.push_back(key);
                    // if next value of argv exists
                    if(i+1 < this->rawArgc) {
                        // if next element is a value of the current option
                        if(this->rawArgv[i+1].find("--") != 0) {
                            // try conversion for int
                            this->optionsValues[key] = std::string(this->rawArgv[i+1]);
                        }
                    }
                }
            }
        }
    }
}

std::string ArgsParser::getOptionValue(ArgsAvailableE option) {

    if(std::find(this->enabledOptions.begin(), this->enabledOptions.end(), option) != this->enabledOptions.end()) {
        if(this->optionsValues[option] == "" || this->optionsValues[option] == "true") return "true";
        else return this->optionsValues[option];
    }
    else return "false";
}


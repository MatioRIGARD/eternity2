#include "utils/args_parser.h"
#include <algorithm>

ArgsParser::ArgsParser() {

}

ArgsParser::~ArgsParser() {

}

void ArgsParser::parse(const int argc, char **argv) {
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
                            this->optionsValues[key] = this->getArgVariantRealType(static_cast<ArgsParser::variant>(std::string(this->rawArgv[i+1])));
                        }
                        // no value, another option
                        else this->optionsValues[key] = static_cast<ArgsParser::variant>(true);
                    }
                    // no value next
                    else this->optionsValues[key] = static_cast<ArgsParser::variant>(true);
                }
            }
        }
    }
}

ArgsParser::variant ArgsParser::getOptionValue(ArgsAvailableE option) {

    if(std::find(this->enabledOptions.begin(), this->enabledOptions.end(), option) != this->enabledOptions.end()) {
        return static_cast<ArgsParser::variant>(this->optionsValues[option]);
    }
    else return false;
}

std::string ArgsParser::getArgsMapString(ArgsAvailableE option) {
    return ArgsParser::argsMap.at(option);
}

ArgsParser::variant ArgsParser::tryGetConvertFromArgVariantToInt(ArgsParser::variant variant) {

    int number = 0;
    try {
        number = std::stoi(std::get<std::string>(variant));
    }
    catch(const std::exception& e) {
        return variant;
    }
    return number;
}

ArgsParser::variant ArgsParser::tryGetConvertFromArgVariantToBool(ArgsParser::variant variant) {
    if(std::get<std::string>(variant) == "true") return true;
    else if(std::get<std::string>(variant) == "false") return false;
    else return variant;
}

ArgsParser::variant ArgsParser::getArgVariantRealType(ArgsParser::variant variant) {
    ArgsParser::variant returnVariant = this->tryGetConvertFromArgVariantToBool(variant);
    return this->tryGetConvertFromArgVariantToInt(returnVariant);
}

#if UNIT_TEST_MODE==1
ArgsParser::variant ArgsParser::unitTestWrapper_tryGetConvertFromArgVariantToInt(ArgsParser::variant variant) {
   return this->tryGetConvertFromArgVariantToInt(variant);
}

ArgsParser::variant ArgsParser::unitTestWrapper_tryGetConvertFromArgVariantToBool(ArgsParser::variant variant) {
    return this->tryGetConvertFromArgVariantToBool(variant);
}

ArgsParser::variant ArgsParser::unitTestWrapper_getArgVariantRealType(ArgsParser::variant variant) {
    return this->getArgVariantRealType(variant);
}
#endif  // UNIT_TEST_MODE



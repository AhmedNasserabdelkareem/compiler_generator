//
// Created by Bassam on 3/20/2019.
//

#ifndef LEXICAL_ANALYZER_STRINGUTILS_H
#define LEXICAL_ANALYZER_STRINGUTILS_H


#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>

using namespace std;

class StringUtils {
public:
    static vector<string> split(const string &string, char delimiter);

    static std::string &ltrim(std::string &str, const std::string &chars = "\t\n\v\f\r ");

    static std::string &rtrim(std::string &str, const std::string &chars = "\t\n\v\f\r ");

    static std::string &trim(std::string &str, const std::string &chars = "\t\n\v\f\r ");
};


#endif //LEXICAL_ANALYZER_STRINGUTILS_H

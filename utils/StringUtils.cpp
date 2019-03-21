//
// Created by Bassam on 3/20/2019.
//

#include <regex>
#include "StringUtils.h"

vector<string> StringUtils::split(const string &string, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(string);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

std::string &StringUtils::trim(std::string &str, const std::string &chars) {
    return ltrim(rtrim(str, chars), chars);
}

std::string &StringUtils::ltrim(std::string &str, const std::string &chars) {
    str.erase(0, str.find_first_not_of(chars));
    return str;
}

std::string &StringUtils::rtrim(std::string &str, const std::string &chars) {
    str.erase(str.find_last_not_of(chars) + 1);
    return str;
}

string StringUtils::replace(string str, char delimiter) {
    string temp=str;
    for(int i = 0; i < temp.length(); i++)
    {
        if(temp[i] == delimiter)
            temp[i] = ' ';
    }
   temp = regex_replace(temp,regex("\\s"), "");
    return temp;
}
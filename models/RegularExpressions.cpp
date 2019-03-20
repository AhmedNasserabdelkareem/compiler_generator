//
// Created by Bassam on 3/19/2019.
//

#include "RegularExpressions.h"

RegularExpressions::RegularExpressions(const unordered_map<string, string> &expressions) : expressions(expressions) {
    constructExpressionsRanges();
}

void RegularExpressions::constructExpressionsRanges() {
    for (const auto &expressionPair: expressions) {
        expressionsRanges[expressionPair.first] = getCharactersRangeFromExpression(expressionPair.second);
    }
}

vector<char> RegularExpressions::getCharactersRangeFromExpression(string expressionName) {

    vector<char> expressionCharactersRange;

    vector<string> separatedRanges = StringUtils::split(expressions[expressionName], OR_OPERATOR);

    for (auto charactersRange : separatedRanges) {

        StringUtils::trim(charactersRange);

        if (charactersRange.find(RANGE_OPERATOR) != string::npos) {
            char startingChar = charactersRange[0];
            char endingChar = charactersRange[charactersRange.length() - 1];

            for (char i = startingChar; i <= endingChar; i++) {
                expressionCharactersRange.push_back(i);
            }
        } else {
            expressionCharactersRange.push_back(charactersRange[0]);
        }
    }

    return expressionCharactersRange;
}

//
// Created by Bassam on 3/19/2019.
//

#include <iostream>
#include "RegularExpressions.h"
#include "RegularDefinitions.h"

RegularExpressions::RegularExpressions(const unordered_map<string, string> &expressions) : expressions(expressions) {
   constructExpressionsRanges();

    addExpression(make_pair(RegularDefinitions::LAMBDA, string(1, LAMBDA)));
}

void RegularExpressions::constructExpressionsRanges() {
    for (const auto &expressionPair: expressions) {
        addExpression(expressionPair);
    }
}

void RegularExpressions::addExpression(const pair<const string, string> &expressionPair) {
    expressionsRanges[expressionPair.first] = getCharactersRangeFromExpression(expressionPair.second);
}

vector<char> RegularExpressions::getCharactersRangeFromExpression(string expressionName) {

    vector<char> expressionCharactersRange;

    vector<string> separatedRanges = StringUtils::split(expressionName, OR_OPERATOR);

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
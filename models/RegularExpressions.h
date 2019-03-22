//
// Created by Bassam on 3/19/2019.
//

#ifndef LEXICAL_ANALYZER_REGULAREXPRESSIONS_H
#define LEXICAL_ANALYZER_REGULAREXPRESSIONS_H

#include <unordered_map>
#include <vector>
#include <utils/StringUtils.h>

using namespace std;

class RegularExpressions {

public:
    unordered_map<string, string> expressions;
    unordered_map<string, vector<char>> expressionsRanges;

public:
    RegularExpressions(const unordered_map<string, string> &expressions);

    vector<char> getCharactersRangeFromExpression(string expressionName);

    void addExpression(const pair<const string, string> &expressionPair);


private:
    const char OR_OPERATOR = '|', RANGE_OPERATOR = '-', LAMBDA = 0;

    void constructExpressionsRanges();

};


#endif //LEXICAL_ANALYZER_REGULAREXPRESSIONS_H

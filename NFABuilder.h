//
// Created by Bassam on 3/19/2019.
//

#ifndef LEXICAL_ANALYZER_NFABUILDER_H
#define LEXICAL_ANALYZER_NFABUILDER_H


#include <models/RegularExpressions.h>
#include <models/RegularDefinitions.h>
#include <models/Keywords.h>
#include <models/TokenStateNode.h>
#include <stack>

class NFABuilder {

public:
    NFABuilder(const RegularDefinitions &regularDefinitions, const RegularExpressions &regularExpressions);

    TokenStateNode getInitialNFANode();

private:

    RegularDefinitions regularDefinitions;
    RegularExpressions regularExpressions;
    TokenStateNode initialNode;
    stack<char> operatorsStack;

private:
    void buildNFATree();

    vector<string> factorizeDefinition(string regularDefinition);

    bool IsLeftParenthesis(const char &character);

    bool IsRightParenthesis(const char &character);

    bool hasHigherPrecedence(const char &testOperator, const char &comparedToOperator);
};


#endif //LEXICAL_ANALYZER_NFABUILDER_H

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

    TokenStateNode initialNode = TokenStateNode(nextStateId++);
    unordered_set<char> charactersSet;

private:

    RegularDefinitions regularDefinitions;
    RegularExpressions regularExpressions;

    stack<char> operatorsStack;
    stack<FiniteStateTable> operandsStack;

    int nextStateId = 0;

private:
    void buildNFATree();

    vector<string> factorizeDefinition(string regularDefinition,unordered_map<string,string> definitions);

    bool isLeftParenthesis(const char &character);

    bool isRightParenthesis(const char &character);

    bool hasHigherPrecedence(const char &testOperator, const char &comparedToOperator);

    bool isOperator(const char &operatorChar);

    void pushToOperands(const string &regex);

    int smallestkeylength (unordered_map<string, string> definitions);

    bool checkKeys(unordered_map<string, string> definitions,string x);

    char getChar(char x);

    void evaluateNextOperands();

    void unionOperands();

    void positiveClosureOperand();

    void kleeneClosureOperand();

    void concatenateOperands();
};


#endif //LEXICAL_ANALYZER_NFABUILDER_H

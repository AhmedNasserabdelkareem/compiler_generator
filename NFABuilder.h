//
// Created by Bassam on 3/19/2019.
//

#ifndef LEXICAL_ANALYZER_NFABUILDER_H
#define LEXICAL_ANALYZER_NFABUILDER_H


#include <models/RegularExpressions.h>
#include <models/RegularDefinitions.h>
#include <models/Keywords.h>
#include <models/TokenStateNode.h>
#include <models/FiniteStateTable.h>
#include <stack>
#include <set>

class NFABuilder {

public:
    NFABuilder(const RegularDefinitions &regularDefinitions, const RegularExpressions &regularExpressions);

    TokenStateNode getInitialNFANode();

    TokenStateNode initialNode;
    set<char> charactersSet;

private:

    RegularDefinitions regularDefinitions;
    RegularExpressions regularExpressions;

    stack<char> operatorsStack;
    stack<FiniteStateTable> operandsStack;

    int nextStateId = 0;

private:
    void buildNFATree();

    bool isLeftParenthesis(const char &character);

    bool isRightParenthesis(const char &character);

    bool hasHigherPrecedence(const char &testOperator, const char &comparedToOperator);

    bool isOperator(const char &operatorChar);

    void pushToOperands(const string &regex);

    char getChar(char x);

    bool checkKeys(unordered_map<string, string> definitions, string x);

    vector<string> factorizeDefinition(string x, unordered_map<string, string> definitions);

    void evaluateNextOperands();

    void concatenateOperands();

    void kleeneClosureOperand();

    void positiveClosureOperand();

    void unionOperands();

    bool isarithmetic(char x);

    vector<string> tokenize(string x,unordered_map<string,string> definitions, vector<string> result);
};


#endif //LEXICAL_ANALYZER_NFABUILDER_H

//
// Created by Bassam on 3/19/2019.
//

#include <models/FiniteStateTable.h>
#include <iostream>
#include "NFABuilder.h"

NFABuilder::NFABuilder(const RegularDefinitions &regularDefinitions, const RegularExpressions &regularExpressions)
        : regularDefinitions(regularDefinitions), regularExpressions(regularExpressions) {
    buildNFATree();
}

TokenStateNode NFABuilder::getInitialNFANode() {
    return initialNode;
}

void NFABuilder::buildNFATree() {

  /*  for (const auto &definition : regularDefinitions.definitions) {

        vector<string> factoredDefinition = factorizeDefinition(definition.second);

        FiniteStateTable stateTable;

        for (const auto &token:factoredDefinition) {

            if (!isOperator(token[0]))
                pushToOperands(token);
            else if (operatorsStack.empty())
                operatorsStack.push(token[0]);
            else if (isLeftParenthesis(token[0]))
                operatorsStack.push(token[0]);
            else if (isRightParenthesis(token[0])) {
                // Evaluate everyting in paranthesis
                while (!isLeftParenthesis(operatorsStack.top()))
                    if (!Eval())
                        return false;
                // Remove left parenthesis after the evaluation
                operatorsStack.pop();
            } else {
                while (!operatorsStack.empty() && hasHigherPrecedence(token[0], operatorsStack.top()))
                    if (!Eval())
                        return false;
                operatorsStack.push(token[0]);
            }
        }

        // Evaluate the rest of operators
        while (!operatorsStack.empty())
            if (!Eval())
                return false;

        // Pop the result from the stack
        if (!Pop(stateTable.statesDequeue))
            return false;

        // Last NFA state is always accepting state
        stateTable.statesDequeue.back()->isAccepting = true;
        stateTable.statesDequeue.back()->stateName = definition.first;

        initialNode.addNextState(RegularExpressions::LAMBDA, stateTable.statesDequeue.front());
    }*/
}

void NFABuilder::pushToOperands(const string &regex) {

}

vector<string> NFABuilder::factorizeDefinition(string x,unordered_map<string,string> definitions) {
    //TODO:Implement by Ahmed Nasser
    vector<string> result ;
    int smallLength = smallestkeylength(definitions);
    int i=0;
    while(i<x.size()){
        char tmp = x[i];
        if(x[i]==' '){
            i++;
            continue;
        }
        if(isalpha(x[i])&&x[i]!='E'&&x[i]!='L'){
            string temp = x.substr(i,smallLength);
            if(checkKeys(definitions,temp)){
                result.push_back(definitions.at(temp));
                i+=smallLength;
                continue;
            }else{
                //TODO I NEED TO CHECK SOME FAULTS IN PDF
            }
        }
        if(x[i]=='+'||x[i]=='*'||x[i]=='|'||x[i]=='.'||x[i]=='('||x[i]==')'||x[i]=='E'){
            if(x[i]=='E'){
                result.push_back(string(1,getChar(x[i])));
                result.push_back(string(1,RegularDefinitions::CONCATENATION));
            } else if(x[i]=='('){
                result.push_back(string(1,RegularDefinitions::CONCATENATION));
                result.push_back(string(1,getChar(x[i])));
            } else if(x[i]==')' && i!=(x.size()-1)){
                result.push_back(string(1,getChar(x[i])));
                result.push_back(string(1,RegularDefinitions::CONCATENATION));
            }else if(x[i]=='.'){
                result.push_back(string(1,RegularDefinitions::CONCATENATION));
                result.push_back(string(1,getChar(x[i])));
                result.push_back(string(1,RegularDefinitions::CONCATENATION));
            }else {
                result.push_back(string(1, getChar(x[i])));
            }
            i++;
            continue;
        }
        if(x[i]=='\\'&&x[i+1]=='L'){
            string temp = x.substr(i,2);
            result.push_back(RegularDefinitions::LAMBDA);
            i+=2;
            continue;
        }
        i++;
    }
/*    for (int i = 0; i < result.size(); ++i) {
        cout<<result[i]<<endl;
    }*/
    return result;
}

/**
 * Returns true if the testOperator has higher precedence than the comparableOperator
 *
 * */
bool NFABuilder::hasHigherPrecedence(const char &testOperator, const char &comparedToOperator) {

    if (testOperator == comparedToOperator)
        return true;

    if (testOperator == RegularDefinitions::KLEENE_CLOSURE || testOperator == RegularDefinitions::POSITIVE_CLOSURE)
        return false;

    if (comparedToOperator == RegularDefinitions::KLEENE_CLOSURE ||
        comparedToOperator == RegularDefinitions::POSITIVE_CLOSURE)
        return true;

    if (testOperator == RegularDefinitions::CONCATENATION)
        return false;

    if (comparedToOperator == RegularDefinitions::CONCATENATION)
        return true;

    if (testOperator == RegularDefinitions::UNION)
        return false;

    return true;
}

bool NFABuilder::isOperator(const char &operatorChar) {
    return operatorChar == RegularDefinitions::UNION || operatorChar == RegularDefinitions::KLEENE_CLOSURE ||
           operatorChar == RegularDefinitions::POSITIVE_CLOSURE || operatorChar == RegularDefinitions::CONCATENATION ||
           isRightParenthesis(operatorChar) || isLeftParenthesis(operatorChar);
}

bool NFABuilder::isLeftParenthesis(const char &character) {
    return character == RegularDefinitions::OPENING_BRACKET;
}

bool NFABuilder::isRightParenthesis(const char &character) {
    return character == RegularDefinitions::CLOSING_BRACKET;
}

int NFABuilder::smallestkeylength(unordered_map<string, string> definitions) {
    int min=1000;
    for (auto& it: definitions) {
        if(it.first.size()<min){
            min=it.first.size();
        }
    }
    return min;
}

bool NFABuilder::checkKeys(unordered_map<string, string> definitions, string x) {
    auto iter = definitions.find(x);
    return iter != definitions.end();
}

char NFABuilder::getChar(char x) {
    switch (x){
        case '*':
            return RegularDefinitions::KLEENE_CLOSURE;
        case '+':
            return RegularDefinitions::POSITIVE_CLOSURE;
        case '|':
            return RegularDefinitions::UNION;
        case '.':
            return RegularDefinitions::DOT;
        case 'E':
            return RegularDefinitions::EXPONENT;
        case '(':
            return RegularDefinitions::OPENING_BRACKET;
        case ')' :
            return RegularDefinitions::CLOSING_BRACKET;
    }
}


//
// Created by Bassam on 3/19/2019.
//

#include <models/FiniteStateTable.h>
#include "NFABuilder.h"

NFABuilder::NFABuilder(const RegularDefinitions &regularDefinitions, const RegularExpressions &regularExpressions)
        : regularDefinitions(regularDefinitions), regularExpressions(regularExpressions) {
    buildNFATree();
}

TokenStateNode NFABuilder::getInitialNFANode() {
    return initialNode;
}

void NFABuilder::buildNFATree() {

    for (const auto &definition : regularDefinitions.definitions) {

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

        initialNode.addNextState(TokenStateNode::LAMBDA, stateTable.statesDequeue.front());
    }

}

void NFABuilder::pushToOperands(const string &regex) {


}

vector<string> NFABuilder::factorizeDefinition(string regularDefinition) {

    //TODO:Implement by Ahmed Nasser
    // You will use regularDefinition and regularExpressions member variables
    return vector<string>();
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
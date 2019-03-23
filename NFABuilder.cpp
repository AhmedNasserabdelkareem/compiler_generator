//
// Created by Bassam on 3/19/2019.
//

#include <models/FiniteStateTable.h>
#include "NFABuilder.h"

NFABuilder::NFABuilder(const RegularDefinitions &regularDefinitions, const RegularExpressions &regularExpressions)
        : regularDefinitions(regularDefinitions), regularExpressions(regularExpressions) {
    buildNFATree();
}

void NFABuilder::buildNFATree() {

    for (const auto &definition : regularDefinitions.definitions) {

        vector<string> factoredDefinition = factorizeDefinition(definition.second);

        for (const auto &token:factoredDefinition) {

            if (!isOperator(token[0])) pushToOperands(token);

            else if (operatorsStack.empty()) operatorsStack.push(token[0]);

            else if (isLeftParenthesis(token[0])) operatorsStack.push(token[0]);

            else if (isRightParenthesis(token[0])) {
                // Evaluate everyting in paranthesis
                while (!isLeftParenthesis(operatorsStack.top())) evaluateNextOperands();
                // Remove left parenthesis after the evaluation
                operatorsStack.pop();
            } else {
                while (!operatorsStack.empty() && hasHigherPrecedence(token[0], operatorsStack.top()))
                    evaluateNextOperands();

                operatorsStack.push(token[0]);
            }
        }

        // Evaluate the rest of operators
        while (!operatorsStack.empty()) evaluateNextOperands();

        // Pop the result from the stack
        FiniteStateTable resultOperand = operandsStack.top();
        operandsStack.pop();

        // Last NFA state is always accepting state
        resultOperand.statesDequeue.back()->isAccepting = true;
        resultOperand.statesDequeue.back()->stateName = definition.first;

        initialNode.addNextState(RegularExpressions::LAMBDA, resultOperand.statesDequeue.front());
    }
}

void NFABuilder::pushToOperands(const string &regex) {

    auto *startNode = new TokenStateNode(nextStateId++);
    auto *endNode = new TokenStateNode(nextStateId++);

    if (regularExpressions.expressions.find(regex) != regularExpressions.expressions.end()) {
        startNode->addNextState(&regularExpressions.expressionsRanges[regex], endNode);

        charactersSet.insert(regularExpressions.expressionsRanges[regex].begin(),
                             regularExpressions.expressionsRanges[regex].end());
    } else {
        startNode->addNextState(regex[0], endNode);

        charactersSet.insert(regex[0]);
    }

    FiniteStateTable operand;
    operand.statesDequeue.push_back(startNode);
    operand.statesDequeue.push_back(endNode);

    operandsStack.push(operand);
}

void NFABuilder::unionOperands() {
    FiniteStateTable secondOperand = operandsStack.top();
    operandsStack.pop();

    FiniteStateTable firstOperand = operandsStack.top();
    operandsStack.pop();

    auto *startNode = new TokenStateNode(nextStateId++);
    auto *endNode = new TokenStateNode(nextStateId++);

    startNode->addNextState(RegularExpressions::LAMBDA, firstOperand.statesDequeue.front());
    startNode->addNextState(RegularExpressions::LAMBDA, secondOperand.statesDequeue.front());

    firstOperand.statesDequeue.back()->addNextState(RegularExpressions::LAMBDA, endNode);
    secondOperand.statesDequeue.back()->addNextState(RegularExpressions::LAMBDA, endNode);

    firstOperand.statesDequeue.push_front(startNode);
    secondOperand.statesDequeue.push_back(endNode);

    firstOperand.statesDequeue.insert(firstOperand.statesDequeue.end(),
                                      secondOperand.statesDequeue.begin(),
                                      secondOperand.statesDequeue.end());

    operandsStack.push(firstOperand);
}

void NFABuilder::positiveClosureOperand() {
    FiniteStateTable operand = operandsStack.top();

    operandsStack.push(operand);

    kleeneClosureOperand();
    concatenateOperands();
}

void NFABuilder::kleeneClosureOperand() {

    FiniteStateTable operand = operandsStack.top();
    operandsStack.pop();

    auto *startNode = new TokenStateNode(nextStateId++);
    auto *endNode = new TokenStateNode(nextStateId++);

    startNode->addNextState(RegularExpressions::LAMBDA, endNode);

    startNode->addNextState(RegularExpressions::LAMBDA, operand.statesDequeue.front());

    operand.statesDequeue.back()->addNextState(RegularExpressions::LAMBDA, endNode);

    operand.statesDequeue.back()->addNextState(RegularExpressions::LAMBDA, operand.statesDequeue.front());

    operand.statesDequeue.push_front(startNode);
    operand.statesDequeue.push_back(endNode);

    operandsStack.push(operand);
}

void NFABuilder::concatenateOperands() {
    FiniteStateTable secondOperand = operandsStack.top();
    operandsStack.pop();

    FiniteStateTable firstOperand = operandsStack.top();
    operandsStack.pop();

    firstOperand.statesDequeue.back()->addNextState(RegularExpressions::LAMBDA, secondOperand.statesDequeue.front());
    firstOperand.statesDequeue.insert(firstOperand.statesDequeue.end(),
                                      secondOperand.statesDequeue.begin(),
                                      secondOperand.statesDequeue.end());

    operandsStack.push(firstOperand);
}


void NFABuilder::evaluateNextOperands() {
    if (!operatorsStack.empty()) {
        char chOperator = operatorsStack.top();
        operatorsStack.pop();

        switch (chOperator) {
            case RegularDefinitions::CONCATENATION:
                concatenateOperands();
                break;
            case RegularDefinitions::KLEENE_CLOSURE:
                kleeneClosureOperand();
                break;
            case RegularDefinitions::POSITIVE_CLOSURE:
                positiveClosureOperand();
                break;
            case RegularDefinitions::UNION:
                unionOperands();
                break;
        }
    }
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

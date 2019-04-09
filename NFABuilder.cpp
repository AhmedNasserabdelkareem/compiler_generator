//
// Created by Bassam on 3/19/2019.
//

#include <models/FiniteStateTable.h>
#include <regex>
#include "NFABuilder.h"

NFABuilder::NFABuilder(const RegularDefinitions &regularDefinitions, const RegularExpressions &regularExpressions)
        : regularDefinitions(regularDefinitions), regularExpressions(regularExpressions) {
    /*   cout<<"EXP"<<regularExpressions.expressions.size()<<endl;
       for (auto& it: regularExpressions.expressions) {
           cout << it.first<<" : "<<it.second<<" "<<endl;
       }
       cout<<"**********************"<<endl;
       cout<<"DEF"<<regularDefinitions.definitions.size()<<endl;
       for (auto& it: regularDefinitions.definitions) {
           cout << it.first<<" : "<<it.second<<" "<<endl;
       }*/

    initialNode.id = nextStateId++;

    buildNFATree();
}

void NFABuilder::buildNFATree() {

    for (const auto &definition : regularDefinitions.definitions) {

        vector<string> factoredDefinition = factorizeDefinition(definition.second, regularExpressions.expressions);
        for (const auto &token:factoredDefinition) {

            if (!isOperator(token[0]) || (isOperator(token[0]) && operandsStack.empty())) pushToOperands(token);

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


        //  cout<<endl;
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
    operandsStack.push(getClone(operandsStack.top()));

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


vector<string> NFABuilder::factorizeDefinition(string x, unordered_map<string, string> definitions) {
    vector<string> pre = StringUtils::split(x, '|');
    //cout<<pre.size();
    vector<string> res;
    for (int j = 0; j < pre.size(); j++) {
        string temp = regex_replace(pre[j], regex("\\s"), "");
        res = tokenize(temp, definitions, res);
        if (j != pre.size() - 1) {
            res.push_back(string(1, '|'));
        }
    }
    return res;
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

bool NFABuilder::checkKeys(unordered_map<string, string> definitions, string x) {
    auto iter = definitions.find(x);
    return iter != definitions.end();
}

char NFABuilder::getChar(char x) {
    switch (x) {
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

bool NFABuilder::isarithmetic(char x) {
    if (x == '=' || x == '>' || x == '<' || x == '!' || x == '\\' || x == '-' || x == '/') {
        return true;
    }
    return false;
}

vector<string> NFABuilder::tokenize(string x, unordered_map<string, string> definitions, vector<string> result) {
    int i = 0;
    string temp = "";
    while (i < x.size()) {
        char tmp = x[i];
        if (x[i] == ' ') {
            i++;
            continue;
        }
        if (isalpha(x[i]) && x[i] != 'E' && x[i] != 'L') {
            while (isalpha(x[i])) {
                temp += x[i];
                if (checkKeys(definitions, temp)) {
                    result.push_back(temp);
                    i++;
                    break;
                } else {

                }
                i++;
            }
            //  cout<<temp<<endl;
            temp = "";
        }
        if (x[i] == '+' || x[i] == '*' || x[i] == '|' || x[i] == '.' || x[i] == '(' || x[i] == ')' || x[i] == 'E') {
            if (x[i] == 'E') {
                result.push_back(string(1, getChar(x[i])));
                result.push_back(string(1, RegularDefinitions::CONCATENATION));
            } else if (x[i] == '(') {
                result.push_back(string(1, RegularDefinitions::CONCATENATION));
                result.push_back(string(1, getChar(x[i])));
            } else if (x[i] == ')' && i != (x.size() - 1) && x[i + 1] != '+' && x[i + 1] != '*') {
                result.push_back(string(1, getChar(x[i])));
                result.push_back(string(1, RegularDefinitions::CONCATENATION));
            } else if (x[i] == '.') {
                result.push_back(string(1, RegularDefinitions::CONCATENATION));
                result.push_back(string(1, getChar(x[i])));
                result.push_back(string(1, RegularDefinitions::CONCATENATION));
            } else {
                result.push_back(string(1, getChar(x[i])));
            }
            i++;
            continue;
        }
        if (x[i] == '\\' && x[i + 1] == 'L') {
            string temp = x.substr(i, 2);
            result.push_back(RegularDefinitions::LAMBDA);
            i += 2;
            continue;
        }
        if (isarithmetic(x[i]) && x[i] != '\\') {
            while (isarithmetic(x[i])) {
                if (x[i] != '\\') {
                    temp += x[i];
                }
                i++;
            }
            result.push_back(temp);
            temp = "";
            i--;
        }
        i++;
    }
    return result;
}

FiniteStateTable NFABuilder::getClone(FiniteStateTable table) {

    FiniteStateTable cloneTable;
    int numberOfNewStates = table.statesDequeue.size();
    nextStateId += numberOfNewStates;
    unordered_map<int, TokenStateNode *> newStates;

    for (auto state:table.statesDequeue) {
        int stateId = state->id + numberOfNewStates;

        TokenStateNode *nodeToInsert = new TokenStateNode(state->stateName, state->isAccepting);
        nodeToInsert->id = stateId;

        newStates[stateId] = nodeToInsert;

        cloneTable.statesDequeue.push_back(nodeToInsert);
    }

    for (auto state:table.statesDequeue) {
        TokenStateNode *newNode = newStates[state->id + numberOfNewStates];

        for (const auto &transitionPair:state->nextStates) {

            vector<TokenStateNode *> nextStates;

            for (auto statesForChar:transitionPair.second) {
                newNode->addNextState(transitionPair.first, newStates[statesForChar->id + numberOfNewStates]);
            }
        }
    }

    return cloneTable;
}


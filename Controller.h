//
// Created by ahmed on 25/03/19.
//

#ifndef COMPILER_GENERATOR_MASTER_CONTROLLER_H
#define COMPILER_GENERATOR_MASTER_CONTROLLER_H

#include <iostream>
#include <models/TokenStateNode.h>

using namespace std;

class Controller {
public:
    Controller(string rules);
    void start();

    void printNodes(TokenStateNode *pNode, unordered_set<int> *visitedStates);

private:
    string rules;

    void printAcceptingStates(TokenStateNode *node, unordered_set<int> *pSet);
};


#endif //COMPILER_GENERATOR_MASTER_CONTROLLER_H

//
// Created by ahmed on 22/03/19.
//

#ifndef COMPILER_GENERATOR_MASTER_DFABUILDER_H
#define COMPILER_GENERATOR_MASTER_DFABUILDER_H


#include <models/TokenStateNode.h>
#include <models/DFAState.h>
#include "NFABuilder.h"

class DFABuilder {
public:
    DFABuilder(TokenStateNode nfa);
    const int lambda = 0;
    void buildDFA();
    bool nodeInStack(DFAState * u, stack<DFAState*> dfaStates);

private:
    TokenStateNode startNFA;
    DFAState* epsilonClosure(TokenStateNode s);
    int counterDFAStates = 0;
    unordered_set<char> charactersSet;
};


#endif //COMPILER_GENERATOR_MASTER_DFABUILDER_H

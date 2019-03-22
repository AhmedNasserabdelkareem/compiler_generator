//
// Created by ahmed on 22/03/19.
//

#ifndef COMPILER_GENERATOR_MASTER_DFABUILDER_H
#define COMPILER_GENERATOR_MASTER_DFABUILDER_H


#include <models/TokenStateNode.h>
#include "NFABuilder.h"

class DFABuilder {
public:
    DFABuilder(TokenStateNode nfa);
    const int lambda = 0;
    void buildDFA();

private:
    TokenStateNode startNFA;
    TokenStateNode* epsilonClosure(TokenStateNode s);
    int counterDFAStates = 0;

};


#endif //COMPILER_GENERATOR_MASTER_DFABUILDER_H

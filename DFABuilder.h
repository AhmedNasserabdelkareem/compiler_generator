//
// Created by ahmed on 22/03/19.
//

#ifndef COMPILER_GENERATOR_MASTER_DFABUILDER_H
#define COMPILER_GENERATOR_MASTER_DFABUILDER_H


#include <models/TokenStateNode.h>
#include <models/DFAState.h>
#include <set>
#include "NFABuilder.h"

class DFABuilder {
public:
    DFABuilder(TokenStateNode nfa, set<char>);
    const int lambda = 0;
    vector<vector<DFAState*> > getDFA();

private:
    TokenStateNode startNFA;
    DFAState* epsilonClosure(TokenStateNode s);
    int counterDFAStates = 0;
    set<char> charactersSet;
    vector<vector<DFAState*> > Dtrans;
    void buildDFA();

};


#endif //COMPILER_GENERATOR_MASTER_DFABUILDER_H

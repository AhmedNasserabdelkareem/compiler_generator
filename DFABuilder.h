//
// Created by ahmed on 22/03/19.
//

#ifndef COMPILER_GENERATOR_MASTER_DFABUILDER_H
#define COMPILER_GENERATOR_MASTER_DFABUILDER_H


#include <models/TokenStateNode.h>
#include <models/DFAState.h>
#include <set>

class DFABuilder {
public:
    DFABuilder(TokenStateNode nfa, set<char>);
    vector<vector<DFAState*> > getDFA();
    DFAState getDFAInitialNode();

private:
    TokenStateNode startNFA;
    int counterDFAStates;
    set<char> charactersSet;
    vector<vector<DFAState*> > Dtrans;
    void buildDFA();
    bool nodeInVector(vector<TokenStateNode>, TokenStateNode*);
//    DFAState epsilonClosure(TokenStateNode s);
    vector<TokenStateNode> epsilonClosure(TokenStateNode n);
    DFAState *startingDFA;

};


#endif //COMPILER_GENERATOR_MASTER_DFABUILDER_H

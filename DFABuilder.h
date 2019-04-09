//
// Created by ahmed on 22/03/19.
//

#ifndef COMPILER_GENERATOR_MASTER_DFABUILDER_H
#define COMPILER_GENERATOR_MASTER_DFABUILDER_H


#include <models/TokenStateNode.h>
#include <models/DFAState.h>
#include <set>
#include <deque>
using namespace std;

class DFABuilder {
public:
    DFABuilder(TokenStateNode nfa, set<char>);
    vector<vector<DFAState> > getDFA();
    DFAState getDFAInitialNode();

private:
    TokenStateNode startNFA;
    int counterDFAStates;
    set<char> charactersSet;
    vector<vector<DFAState> > Dtrans;
    void buildDFA();
    bool nodeInVector(vector<TokenStateNode>, TokenStateNode*);
//    DFAState epsilonClosure(TokenStateNode s);
    vector<TokenStateNode> epsilonClosure(TokenStateNode n);
    DFAState *startingDFA;

    int findInVector(DFAState *pState, vector<vector<DFAState> > pDeque);

    bool compareVectors(vector<TokenStateNode> vector, std::vector<TokenStateNode> states);

    vector<vector<DFAState>> normalizeDFAStates(vector<vector<DFAState>> vector);

    void printDFAStates(vector<vector<DFAState>> vector);

    void printAcceptance(vector<vector<DFAState>> vector);
};


#endif //COMPILER_GENERATOR_MASTER_DFABUILDER_H

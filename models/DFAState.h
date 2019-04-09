//
// Created by ahmed on 22/03/19.
//

#ifndef COMPILER_GENERATOR_MASTER_DFASTATE_H
#define COMPILER_GENERATOR_MASTER_DFASTATE_H


#include "TokenStateNode.h"

class DFAState {

public:
    DFAState(vector<TokenStateNode> formingStates, int id);
    void addNextState(char character, DFAState *state);
    DFAState * move(char input, int id);
    void markForConversion();
    void unMarkForConversion();
    bool equals(DFAState *state);
    bool isAcceptance();

    string getToken();

public:
    unordered_map<char, vector<DFAState *>> nextDFAStates;
    vector<TokenStateNode> formingNFAStates;
    int id = -1;

private:
    bool markedForConversion = false;

    vector<TokenStateNode> eClosure(TokenStateNode n);

    bool nodeInVector(vector<TokenStateNode> v, TokenStateNode *n);
};


#endif //COMPILER_GENERATOR_MASTER_DFASTATE_H

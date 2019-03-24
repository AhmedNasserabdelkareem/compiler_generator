//
// Created by ahmed on 22/03/19.
//

#ifndef COMPILER_GENERATOR_MASTER_DFASTATE_H
#define COMPILER_GENERATOR_MASTER_DFASTATE_H


#include "TokenStateNode.h"

class DFAState {

public:
    DFAState(vector<TokenStateNode *> formingStates);
    void addNextState(char character, DFAState *state);
    DFAState * move(char input);
    void markForConversion();
    bool equals(DFAState *state);


public:
    unordered_map<char, vector<DFAState *>> nextDFAStates;
    vector<TokenStateNode *> formingDFAStates;

private:
    bool markedForConversion = false;
};


#endif //COMPILER_GENERATOR_MASTER_DFASTATE_H

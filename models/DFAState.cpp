//
// Created by ahmed on 22/03/19.
//

#include "DFAState.h"
DFAState:: DFAState(vector<TokenStateNode *> s, int x){
    formingDFAStates = s;
    id = x;
}

void DFAState::addNextState(char character, DFAState *state) {
    nextDFAStates[character].push_back(state);
}

DFAState* DFAState::move(char input, int dfaStateID){
    vector<TokenStateNode *> formation;
    for(int i = 0; i < formingDFAStates.size(); i++){
        //
        vector<TokenStateNode *> v = formingDFAStates[i]->getStatesForCharacter(input);
        for(int j = 0; j < v.size(); j++){
            formation.push_back(v[j]);
        }
    }
    return new DFAState(formation, dfaStateID);
}

void DFAState:: markForConversion(){
    markedForConversion = true;
}
void DFAState:: unMarkForConversion(){
    markedForConversion = false;
}


bool DFAState::equals(DFAState *x){
    return  this->id == x->id;
}
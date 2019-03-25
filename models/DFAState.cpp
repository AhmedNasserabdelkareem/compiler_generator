//
// Created by ahmed on 22/03/19.
//

#include "DFAState.h"
DFAState:: DFAState(vector<TokenStateNode *> s, int x){
    formingNFAStates = s;
    id = x;
}

void DFAState::addNextState(char character, DFAState *state) {
    if (nextDFAStates.find(character) == nextDFAStates.end()) {
        nextDFAStates[character] = vector<DFAState *>();
    };
    nextDFAStates[character].push_back(state);
}

DFAState* DFAState::move(char input, int dfaStateID){
    vector<TokenStateNode *> formation;
    for(int i = 0; i < formingNFAStates.size(); i++){
        //
        vector<TokenStateNode *> v = formingNFAStates[i]->getStatesForCharacter(input);
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

bool DFAState::isAcceptance() {
    for(int i = 0; i < formingNFAStates.size(); i++){
        if(formingNFAStates[i]->isAccepting) return true;
    }
    return false;
}
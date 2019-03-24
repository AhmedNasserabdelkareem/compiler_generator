//
// Created by ahmed on 22/03/19.
//

#include "DFAState.h"
DFAState:: DFAState(vector<TokenStateNode *> s){
    formingDFAStates = s;
}

void DFAState::addNextState(char character, DFAState *state) {
    nextDFAStates[character].push_back(state);
}

DFAState* DFAState::move(char input){

}

void DFAState:: markForConversion(){
    markedForConversion = true;
}

bool DFAState::equals(DFAState *x){
    if(x->formingDFAStates.size() != this->formingDFAStates.size()) return false;
    //todo
}
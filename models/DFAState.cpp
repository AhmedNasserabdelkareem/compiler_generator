//
// Created by ahmed on 22/03/19.
//

#include <set>
#include "DFAState.h"
DFAState:: DFAState(vector<TokenStateNode> s, int x){
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
    vector<TokenStateNode> formation;
    for(int i = 0; i < formingNFAStates.size(); i++){
        //
        vector<TokenStateNode *> v = formingNFAStates[i].getStatesForCharacter(input);
        for(int j = 0; j < v.size(); j++){
            formation.push_back(*v[j]);
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
    vector<TokenStateNode> formation1 = this->formingNFAStates;
    vector<TokenStateNode> formation2 = x->formingNFAStates;
    if(formation1.size() != formation2.size()) return false;
    std::set<int> cmp;
    for(int i = 0; i < formation1.size(); i++){
        cmp.insert(formation1[i].id);
        cmp.insert(formation2[i].id);
    }
    return cmp.size() == formation2.size();
}

bool DFAState::isAcceptance() {
    for(int i = 0; i < formingNFAStates.size(); i++){
        if(formingNFAStates[i].isAccepting) return true;
    }
    return false;
}
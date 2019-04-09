//
// Created by ahmed on 22/03/19.
//

#include <set>
#include <DFABuilder.h>
#include "RegularExpressions.h"

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
        vector<TokenStateNode *> v = formingNFAStates[i].getStatesForCharacter(input);
        for(int j = 0; j < v.size(); j++){
            formation.push_back(*v[j]);
            vector<TokenStateNode> epsilonStates = eClosure(*v[j]);
            for (int k = 0; k < epsilonStates.size(); k++) {
                formation.push_back(epsilonStates[k]);
            }
        }
    }
    return new DFAState(formation, dfaStateID);
}

vector<TokenStateNode> DFAState::eClosure(TokenStateNode n) {
    deque<TokenStateNode *> q;
    vector<TokenStateNode> formation;
//    formation.push_back(n);
    vector<TokenStateNode *> initialStates = n.getStatesForCharacter(RegularExpressions::LAMBDA);
    for (int i = 0; i < initialStates.size(); i++) {
        q.insert(q.begin(), initialStates[i]);
    }
    while (!q.empty()) {
        TokenStateNode *u = q.front();
        q.pop_front();
        vector<TokenStateNode *> innerETransitions = u->getStatesForCharacter(RegularExpressions::LAMBDA);
        for (int i = 0; i < innerETransitions.size(); i++) {
            q.insert(q.begin(), innerETransitions[i]);
        }
        if (!nodeInVector(formation, u)) formation.push_back(*u);
    }
    return formation;
}

bool DFAState::nodeInVector(vector<TokenStateNode> v, TokenStateNode *n) {
    for (int i = 0; i < v.size(); i++) {
        if (n->id == v[i].id) return true;
    }
    return false;
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

string DFAState::getToken() {
    for (int i = 0; i < formingNFAStates.size(); i++) {
        if (formingNFAStates[i].isAccepting) return formingNFAStates[i].stateName;
    }
    return "";
}

bool DFAState::isAcceptance() {
    for(int i = 0; i < formingNFAStates.size(); i++){
        if(formingNFAStates[i].isAccepting) return true;
    }
    return false;
}
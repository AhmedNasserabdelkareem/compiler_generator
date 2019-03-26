//
// Created by ahmed on 22/03/19.
//

#include <models/DFAState.h>
#include "DFABuilder.h"
#include <algorithm>
#include <deque>
#include <models/RegularExpressions.h>
#include <stack>


DFABuilder::DFABuilder(TokenStateNode node, set<char> language): startNFA(node){
    charactersSet = language;
    counterDFAStates = 0;
    vector<TokenStateNode> formation = epsilonClosure(startNFA);
    DFAState x(formation, counterDFAStates++);
    this->startingDFA = &x;
    buildDFA();
}

void DFABuilder::buildDFA() {
    deque<DFAState *> *dfaStates = new deque<DFAState *>;

    dfaStates->insert(dfaStates->begin(), startingDFA);
    while (!dfaStates->empty()){
        DFAState *t = dfaStates->front();
        dfaStates->pop_front();
        t->markForConversion();

        vector<DFAState *> v;
        for(auto itr = charactersSet.begin(); itr != charactersSet.end(); ++itr){
            DFAState *u = t->move(*itr, counterDFAStates++);
            t->addNextState(*itr, u);
            if( find(dfaStates->begin(), dfaStates->end(), u) == dfaStates->end()){
                u->unMarkForConversion();
                dfaStates->insert(dfaStates->begin(), u);
            }
            //update result dfa
            v.push_back(u);
        }
        Dtrans.push_back(v);
        v = vector<DFAState *>(); //for deallocation
    }

}

vector<TokenStateNode> DFABuilder::epsilonClosure(TokenStateNode n) {
    deque<TokenStateNode *> q;
    vector<TokenStateNode> formation;
    formation.push_back(n);
    vector<TokenStateNode *> initialStates = n.getStatesForCharacter(RegularExpressions::LAMBDA);
    for(int i = 0; i < initialStates.size(); i++){
        q.insert(q.begin(), initialStates[i]);
    }
    while(!q.empty()){
        TokenStateNode *u = q.front();
        q.pop_front();
        vector<TokenStateNode *> innerETransitions = u->getStatesForCharacter(RegularExpressions::LAMBDA);
        for(int i = 0; i < innerETransitions.size(); i++){
            q.insert(q.begin(), innerETransitions[i]);
        }
        if(!nodeInVector(formation, u)) formation.push_back(*u);
    }
    return formation;
}


vector<vector<DFAState*> > DFABuilder::getDFA(){
    return Dtrans;
}
DFAState DFABuilder::getDFAInitialNode(){
    return *startingDFA;
}

bool DFABuilder::nodeInVector(vector<TokenStateNode> v, TokenStateNode *n){
    for(int i = 0; i < v.size(); i++){
        if(n == &v[i]) return true;
    }
    return false;
}
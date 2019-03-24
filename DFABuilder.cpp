//
// Created by ahmed on 22/03/19.
//

#include <models/DFAState.h>
#include "DFABuilder.h"
#include <algorithm>

DFABuilder::DFABuilder(TokenStateNode node): startNFA(node){
    buildDFA();
}

void DFABuilder::buildDFA() {
    deque<DFAState *> *dfaStates = new deque<DFAState *>;
    deque<DFAState *>::iterator it = dfaStates->begin();
    dfaStates->insert(it, epsilonClosure(startNFA));

    while (!dfaStates->empty()){
        DFAState *t = dfaStates->front();
        dfaStates->pop_front();
        t->markForConversion();

        vector<DFAState *> v;
        for(auto itr = charactersSet.begin(); itr != charactersSet.end(); ++itr){
            DFAState *u = t->move(*itr, counterDFAStates++);
            if( find(dfaStates->begin(), dfaStates->end(), u) == dfaStates->end()){
                u->unMarkForConversion();
                dfaStates->insert(it, u);
            }
            //update result dfa
            v.push_back(u);
        }
        Dtrans.push_back(v);
        v = vector<DFAState *>(); //for deallocation
    }

}

//needs to handle case when a - b - c - d
// a (lambda) = c
// c(lambda) = d
//epsilon closure is a + c + d
//here we get only c as e closure of a
DFAState* DFABuilder::epsilonClosure(TokenStateNode s) {
    DFAState *result = new DFAState(s.getStatesForCharacter(lambda), counterDFAStates++);
    return result;
}

vector<vector<DFAState*> > DFABuilder::getDFA(){
    return Dtrans;
}
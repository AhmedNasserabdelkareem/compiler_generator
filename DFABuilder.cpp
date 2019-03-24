//
// Created by ahmed on 22/03/19.
//

#include <models/DFAState.h>
#include "DFABuilder.h"

DFABuilder::DFABuilder(TokenStateNode node): startNFA(node){
}

void DFABuilder::buildDFA() {
    stack<DFAState *> *dfaStates = new stack<DFAState *>;
    dfaStates->push(epsilonClosure(startNFA));
    while (!dfaStates->empty()){
        DFAState *t = dfaStates->top();
        t->markForConversion();
        dfaStates->pop();
        for(auto itr = charactersSet.begin(); itr != charactersSet.end(); ++itr){
            DFAState *u = t->move(*itr);
            if(!nodeInStack(u, dfaStates)) dfaStates->push(u);
        }
        //update edge
    }

}

//needs to handle case when a - b - c - d
// a (lambda) = c
// c(lambda) = d
//epsilon closure is a + c + d
//here we get only c as e closure of a
DFAState* DFABuilder::epsilonClosure(TokenStateNode s) {
    DFAState *result = new DFAState(s.getStatesForCharacter(lambda));
    return result;
}

bool DFAState:: nodeInStack(DFAState * u, stack<DFAState*> dfaStates) {
    for(int i = 0; i < dfaStates.size(); i++){
        if(u->equals(dfaStates.top()) ) return true;
        dfaStates.pop();
    }
    return false;
}


//
// Created by ahmed on 22/03/19.
//

#include "DFABuilder.h"

DFABuilder::DFABuilder(TokenStateNode node): startNFA(node){
}

void DFABuilder::buildDFA() {

}

//needs to handle case when a - b - c - d
// a (lambda) = c
// c(lambda) = d
//epsilon closure is a + c + d
//here we get only c as e closure of a
TokenStateNode* DFABuilder::epsilonClosure(TokenStateNode s) {
    vector<TokenStateNode *> states = s.getStatesForCharacter(lambda);
    TokenStateNode *eNode = new TokenStateNode(counterDFAStates++);
    for(int i = 0; i < states.size(); i++){
        eNode->addNextState(states[i]);
    }
    return eNode;
}
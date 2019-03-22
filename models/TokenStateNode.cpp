//
// Created by Bassam on 3/19/2019.
//

#include "TokenStateNode.h"

int TokenStateNode::staticID = 0;

TokenStateNode::TokenStateNode() : id(DEFAULT_ID) {}

TokenStateNode::TokenStateNode(int id) : id(id) {}

void TokenStateNode::addNextState(char character, TokenStateNode *state) {

    if (nextStates.find(character) != nextStates.end()) {
        nextStates[character] = vector<TokenStateNode *>();
    }
    nextStates[character].push_back(state);
}

void TokenStateNode::removeStatesForCharacter(char character) {
    nextStates.erase(character);
}

vector<TokenStateNode *> TokenStateNode::getStatesForCharacter(char character) {
    return nextStates[character];
}



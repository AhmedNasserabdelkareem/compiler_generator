//
// Created by Bassam on 3/19/2019.
//

#ifndef LEXICAL_ANALYZER_TOKENSTATENODE_H
#define LEXICAL_ANALYZER_TOKENSTATENODE_H

#include <unordered_map>

using namespace std;

class TokenStateNode {


public:

    const string INVALID_STATE = "invalid_state";
    const bool DEFAULT_ACCEPTING = false, DEFAULT_KLEENE_CLOSURE = false;
    const char LAMBDA = 0;

    bool isAccepting = DEFAULT_ACCEPTING, isKleeneClosure = DEFAULT_KLEENE_CLOSURE;
    string stateName = INVALID_STATE; //Equivalent to the definition name when it's an accepting state
    unordered_map<char, TokenStateNode*> nextStates;

public:
    bool isLambda(char character);
};


#endif //LEXICAL_ANALYZER_TOKENSTATENODE_H

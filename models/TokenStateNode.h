//
// Created by Bassam on 3/19/2019.
//

#ifndef LEXICAL_ANALYZER_TOKENSTATENODE_H
#define LEXICAL_ANALYZER_TOKENSTATENODE_H

#include <unordered_map>
#include <vector>

using namespace std;

class TokenStateNode {
public:
    TokenStateNode();

    explicit TokenStateNode(int id);

    TokenStateNode(string name, bool accept): id(staticID++), stateName(name), isAccepting(accept){

    }

    void addNextState(char character, TokenStateNode *state);

    void removeStatesForCharacter(char character);

    vector<TokenStateNode *> getStatesForCharacter(char character);

public:
    string INVALID_STATE = "invalid_state";
    static const bool DEFAULT_ACCEPTING = false;
    static const int DEFAULT_ID = -1;

public:
    int id = DEFAULT_ID;
    bool isAccepting = DEFAULT_ACCEPTING;
    string stateName = INVALID_STATE; //Equivalent to the definition name when it's an accepting state

private:
    unordered_map<char, vector<TokenStateNode *>> nextStates;
    static int staticID;
};


#endif //LEXICAL_ANALYZER_TOKENSTATENODE_H

//
// Created by sharaf on 08/04/2019.
//

#ifndef COMPILER_GENERATOR_MASTER_TOKENGENERATOR_H
#define COMPILER_GENERATOR_MASTER_TOKENGENERATOR_H

#include <vector>

#include <models/DFAminiState.h>
#include <set>
#include <string>
#include <fstream>
#include <streambuf>
#include <unordered_set>

#define STARTING_STATE_ID 0

class TokenGenerator {
public:
    TokenGenerator(vector<vector<DFAminiState>> minimizedDfa, set<char> inputs,
                       unordered_set<string> punc, unordered_set<string> keywords);

//    vector<string> generateTokens(ifstream file);
    vector<string> generateTokens(string inputStream);


private:
    vector<vector<DFAminiState> > minimizedDfa;
    set<char> inputs;
    unordered_set<string> keywords, punc;


    bool getToken(vector<string> &tokens, int lastAcceptingInput, DFAminiState &lastAcceptingState,
                                  DFAminiState &idleState,int &crrentStateId, int &i, string inputStream, bool endWithPunc);

    string isKeyword(int i, string inputStream, bool endWithPunc);

    string isPunc(char c);
};


#endif //COMPILER_GENERATOR_MASTER_TOKENGENERATOR_H

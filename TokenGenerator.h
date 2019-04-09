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

#define STARTING_STATE_ID 0

class TokenGenerator {
public:
    TokenGenerator(vector<vector<DFAminiState> > minimizedDfa, set<char> inputs);

//    vector<string> generateTokens(ifstream file);
    vector<string> generateTokens(string inputStream);


private:
    vector<vector<DFAminiState> > minimizedDfa;
    set<char> inputs;


    bool
    getToken(vector<string> &tokens, int lastAcceptingInput, DFAminiState *&lastAcceptingState, int &crrentStateId,
             int &i) const;
};


#endif //COMPILER_GENERATOR_MASTER_TOKENGENERATOR_H

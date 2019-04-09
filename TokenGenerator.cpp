#include <utility>

#include <iostream>

//
// Created by sharaf on 08/04/2019.
//

#include "TokenGenerator.h"

TokenGenerator::TokenGenerator(vector<vector<DFAminiState> > minimizedDfa, set<char> inputs) : minimizedDfa(
        std::move(minimizedDfa)), inputs(std::move(inputs)) {};

/*vector<string> TokenGenerator::generateTokens(ifstream file) {
    string inputStream((std::istreambuf_iterator<char>(file)),
               std::istreambuf_iterator<char>());
    return generateTokens(inputStream);
}*/

vector<string> TokenGenerator::generateTokens(string inputStream) {
    vector<string> tokens;

    DFAminiState *lastAcceptingState = nullptr, *tempState;
    int crrentStateId = STARTING_STATE_ID, inputIndex, lastAcceptingInput = 0;
    char input;

    for (int i = 0; i < inputStream.size(); i++) {
        input = inputStream[i];
        if (input == ' ' || input == '\t' || input == '\n') {
            if (i == 0)
                continue;
            else {
                char prev = inputStream[i - 1];
                if (prev == ' ' || prev == '\t' || prev == '\n')
                    continue;
                else if (!getToken(tokens, lastAcceptingInput, lastAcceptingState, crrentStateId, i))//if not => error
                    return tokens;
            }
        }

        inputIndex = std::distance(inputs.begin(), inputs.find(input));
        if (inputIndex >= inputs.size()) {
            //input dosen't exist
        } else {
            tempState = &minimizedDfa[crrentStateId][inputIndex + 1];
            crrentStateId = tempState->id;
            if (tempState->isAccepting) {
                lastAcceptingState = tempState;
                lastAcceptingInput = i;
            }
        }

        if (i == inputStream.size() - 1) {
            if (!getToken(tokens, lastAcceptingInput, lastAcceptingState, crrentStateId, i))//if not => error
                return tokens;
        }
    }

    return tokens;
}

bool TokenGenerator::getToken(vector<string> &tokens, int lastAcceptingInput, DFAminiState *&lastAcceptingState,
                              int &crrentStateId, int &i) const {
    if (lastAcceptingState != nullptr) {
        tokens.push_back(lastAcceptingState->token);
        //cout<<lastAcceptingState->token;
        i = lastAcceptingInput + 1;
        lastAcceptingState = nullptr;
        crrentStateId = STARTING_STATE_ID;
        return true;
    } else {
        //ERROR massage
        return false;
    }
}


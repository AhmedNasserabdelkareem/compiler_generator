#include <utility>

#include <iostream>

//
// Created by sharaf on 08/04/2019.
//

#include "TokenGenerator.h"

TokenGenerator::TokenGenerator(vector<vector<DFAminiState>> minimizedDfa, set<char> inputs,
                               unordered_set<string> punc, unordered_set<string> keywords)
        : minimizedDfa(
        std::move(minimizedDfa)), inputs(std::move(inputs)), punc(punc), keywords(keywords) {};

/*vector<string> TokenGenerator::generateTokens(ifstream file) {
    string inputStream((std::istreambuf_iterator<char>(file)),
               std::istreambuf_iterator<char>());
    return generateTokens(inputStream);
}*/

vector<string> TokenGenerator::generateTokens(string inputStream) {
    vector<string> tokens;

    DFAminiState idleState = DFAminiState("idle", false, -99, "");
    DFAminiState lastAcceptingState = idleState, tempState;
    int crrentStateId = STARTING_STATE_ID, inputIndex, lastAcceptingInput = 0;
    char input;

    for (int i = 0; i < inputStream.size(); i++) {
        input = inputStream[i];
        if (input == ' ' || input == '\t' || input == '\n') {
            if (i == 0)
                continue;
            else {
                char prev = inputStream[i - 1];
                if (prev == ' ' || prev == '\t' || prev == '\n' || !isPunc(prev).empty())
                    continue;
                else if (!getToken(tokens, lastAcceptingInput, lastAcceptingState, idleState, crrentStateId,
                                   i, inputStream, false))//if not => error
                    return tokens;
            }
        }

        string punc = isPunc(input);
        if (!punc.empty()){
            if (i > 0 && inputStream[i - 1] != ' ' &&  inputStream[i - 1] != '\t' &&  inputStream[i - 1] != '\n'
                    && isPunc(inputStream[i - 1]).empty()) {
                if (!getToken(tokens, lastAcceptingInput, lastAcceptingState, idleState, crrentStateId,
                              i, inputStream, true))//if not => error
                    return tokens;
            }

            tokens.push_back(punc);
            continue;
        }

        inputIndex = std::distance(inputs.begin(), inputs.find(input));
        if (inputIndex >= inputs.size()) {
            //input dosen't exist
        } else {
            tempState = minimizedDfa[crrentStateId][inputIndex];
            crrentStateId = tempState.id;
            if (tempState.isAccepting) {
                lastAcceptingState = tempState;
                lastAcceptingInput = i;
            }
        }

        if (i == inputStream.size() - 1) {
            if (!getToken(tokens, lastAcceptingInput, lastAcceptingState, idleState, crrentStateId, i,
                          inputStream, false))//if not => error
                return tokens;
        }
    }

    return tokens;
}

bool TokenGenerator::getToken(vector<string> &tokens, int lastAcceptingInput, DFAminiState &lastAcceptingState,
                              DFAminiState &idleState, int &crrentStateId, int &i, string inputStream, bool endWithPunc) {
    if (lastAcceptingState.id != idleState.id) {
        string token = lastAcceptingState.token, temp;
        temp = isKeyword(i, inputStream, endWithPunc);
        if (temp.empty())//not keyword
            tokens.push_back(token);
        else
            tokens.push_back(temp);

        //cout<<lastAcceptingState->token;
        i = lastAcceptingInput + 1;
        lastAcceptingState = idleState;
        crrentStateId = STARTING_STATE_ID;
        return true;
    } else {
        //ERROR massage
        return false;
    }
}

string TokenGenerator::isKeyword(int i, string inputStream, bool endWithPunc) {
    string result = "";
    int start = 0;
    if (i != inputStream.size() - 1 || endWithPunc)
        i--;
    for (int j = i - 1; j >= 0; j--) {
        if (inputStream[j] == ' ' || !isPunc(inputStream[j]).empty() || inputStream[j] == ';') {
            start = j + 1;
            break;
        }
    }

    string temp = inputStream.substr(start, i - start + 1);
    int idIndex = std::distance(keywords.begin(), keywords.find(temp));
    if (idIndex < keywords.size())
        result = temp;

//    for (auto it = keywords.begin(); it != keywords.end(); ++it) {
//        cout << *it << " ";
//    }

    return result;

}

string TokenGenerator::isPunc(char c) {
    string result = "", temp (1 , c);

//    for (auto it = punc.begin(); it != punc.end(); ++it) {
//        cout << *it << " ";
//    }

    int idIndex = std::distance(punc.begin(), punc.find(temp));
    if (idIndex < punc.size() || temp == ";")
        result = temp;

    return result;
}


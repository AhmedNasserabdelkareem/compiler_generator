//
// Created by sharaf on 19/03/2019.
//

#include <sstream>
#include <iostream>
#include "DFAmini.h"

vector<vector<TokenStateNode> > DFAmini::getMinimizedDFA(vector<vector<TokenStateNode> > dfa) {

    vector<vector<TokenStateNode> > newStates = states;
    bool stateAdded;

    do {
        states = newStates;
        newStates.clear();
        for (int i = 0; i < states.size(); ++i) {

            if (states[i].size() == 1) {//class has only one state so add it to newStates immediately
                newStates.push_back(states[i]);
            } else {
                vector<TokenStateNode> firstState(1, states[i][0]);
                int startCheckingClassesFrom = newStates.size();//first classes won't be equivalent so check from last one and newly added
                newStates.push_back(firstState); //push the first element in the class to a new class
                for (int j = 1; j < states[i].size(); ++j) {
                    stateAdded = false;
                    for (int k = startCheckingClassesFrom; !stateAdded && k < newStates.size(); ++k) {
                        if (isEquivalentStates(dfa, states[i][j].id, newStates[k][0].id)) {
                            newStates[k].push_back(states[i][j]);
                            stateAdded = true;
                        }
                    }

                    if (!stateAdded) {//no equivalent classes so add it in a new class
                        vector<TokenStateNode> newClass(1, states[i][j]);
                        newStates.push_back(newClass);
                    }
                }
            }

        }
    } while (newStates.size() != states.size());

    return renameStates(dfa);
}

vector<vector<TokenStateNode> > DFAmini::getZeroEquivalent(vector<vector<TokenStateNode> > dfa) {

    for (int i = 0; i < dfa.size(); ++i) {
        if (!dfa[i][0].isAccepting)
            states[0].push_back(dfa[i][0]);
        else
            states[1].push_back(dfa[i][0]);
    }

}

bool
DFAmini::isEquivalentStates(vector<vector<TokenStateNode> > dfa, int stateA, int stateB) {
    if (dfa[stateA].size() != dfa[stateB].size())
        return false;

    for (int i = 0; i < dfa[stateA].size(); ++i) {
        if (!isInSameClass(dfa[stateA][i].id, dfa[stateB][i].id))
            return false;
    }

    return true;
}

bool DFAmini::isInSameClass(int stateA, int stateB) {
    bool found = false, sameClass = false;
    for (int i = 0; !found && i < states.size(); ++i) {
        for (int j = 0; !found && j < states[i].size(); ++j) {
            if (stateA == states[i][j].id) {
                found = true;
                for (int k = j; k < states[i].size(); ++k) {
                    if (stateB == states[i][k].id) {
                        sameClass = true;
                        break;
                    }
                }
            }

            if (!found && stateB == states[i][j].id) {
                found = true;
                for (int k = j; k < states[i].size(); ++k) {
                    if (stateA == states[i][k].id) {
                        sameClass = true;
                        break;
                    }
                }
            }

        }
    }

    return sameClass;
}

vector<vector<TokenStateNode> > DFAmini::renameStates(vector<vector<TokenStateNode> > dfa){
    vector<vector<TokenStateNode> > minimized(0, vector<TokenStateNode>());
    bool nextInput, added;

    for (int i = 0; i < dfa.size(); ++i) {
        added = false;

        for (int j = 0; !added && j < states.size(); ++j) {
            if (dfa[i][0].id == states[j][0].id){
                vector<TokenStateNode> state(1, TokenStateNode(concatenateName(j), states[j][0].isAccepting));
                minimized.push_back(state);
                added = true;
            }
        }

        for (int k = 1; added && k < dfa[i].size(); ++k) {
            nextInput = false;
            for (int j = 0; !nextInput && j < states.size(); ++j) {
                for (int l = 0; !nextInput && l < states[j].size(); ++l) {
                    if (dfa[i][k].id == states[j][l].id){
                        minimized[minimized.size() - 1].push_back(TokenStateNode(concatenateName(j), states[j][l].isAccepting));
                        nextInput = true;
                    }
                }
            }
        }

    }
    return minimized;
}

void DFAmini::printMinimizedStates() {

    cout << endl;
    for (int i = 0; i < states.size(); ++i) {
        for (int j = 0; j < states[i].size(); ++j) {
            cout << states[i][j].stateName << " ";
        }
        cout << endl;
    }

}

string DFAmini::concatenateName(int num){
    std::stringstream ss;
    ss << "S" << num;
    return ss.str();
}

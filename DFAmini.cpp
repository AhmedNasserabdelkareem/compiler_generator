//
// Created by sharaf on 19/03/2019.
//

#include <sstream>
#include <models/DFAState.h>
#include <models/DFAminiState.h>
#include <iostream>
#include "DFAmini.h"

vector<vector<DFAminiState> > DFAmini::getMinimizedDFA(vector<vector<DFAState> > dfa) {

         //sortDFA(&dfa);
         getZeroEquivalent(dfa);
    vector<vector<DFAState> > newStates = states;
    bool stateAdded;

    do {
        states = newStates;
        newStates.clear();
        for (int i = 0; i < states.size(); ++i) {

            if (states[i].size() == 0) {
                continue;
            } else if (states[i].size() == 1) {//class has only one state so add it to newStates immediately
                newStates.push_back(states[i]);
            } else {
                vector<DFAState> firstState(1, states[i][0]);
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
                        vector<DFAState> newClass(1, states[i][j]);
                        newStates.push_back(newClass);
                    }
                }
            }

        }
    } while (newStates.size() != states.size());

    return renameStates(dfa);
}

void DFAmini::getZeroEquivalent(vector<vector<DFAState> > dfa) {
    for (int i = 0; i < dfa.size(); ++i) {
        //cout << dfa[i][0].isAcceptance();
        if (!dfa[i][0].isAcceptance())
            states[0].push_back(dfa[i][0]);
        else
            states[1].push_back(dfa[i][0]);
    }

}

bool
DFAmini::isEquivalentStates(vector<vector<DFAState> > dfa, int stateA, int stateB) {
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

vector<vector<DFAminiState> > DFAmini::renameStates(vector<vector<DFAState> > dfa) {
    vector<vector<DFAminiState> > minimized(0, vector<DFAminiState>());
    bool nextInput, added;
    DFAminiState deadState = DFAminiState("de", false, -1, "");

    for (int i = 0; i < dfa.size(); ++i) {
        added = false;

        for (int j = 0; !added && j < states.size(); ++j) {
            if (dfa[i][0].id == states[j][0].id) {
                vector<DFAminiState> state(1, DFAminiState(concatenateName(j), states[j][0].isAcceptance(), j,
                                                           states[j][0].getToken()));
                minimized.push_back(state);
                added = true;
            }
        }

        for (int k = 1; added && k < dfa[i].size(); ++k) {
            nextInput = false;
            for (int j = 0; !nextInput && j < states.size(); ++j) {
                for (int l = 0; !nextInput && l < states[j].size(); ++l) {
                    if (dfa[i][k].id == -1){
                        minimized[minimized.size() - 1].push_back(deadState);
                        nextInput = true;
                    }else if (dfa[i][k].id == states[j][l].id) {
                        minimized[minimized.size() - 1].push_back(
                                DFAminiState(concatenateName(j), states[j][l].isAcceptance(), j,
                                             states[j][l].getToken()));
                        nextInput = true;
                    }
                }
            }
        }

    }
    sortDFAmini(&minimized);
    return minimized;
}

void DFAmini::printMinimizedStates() {

    cout << endl;
    for (int i = 0; i < states.size(); ++i) {
        for (int j = 0; j < states[i].size(); ++j) {
            cout << states[i][j].id << " ";
        }
        cout << endl;
    }

}

string DFAmini::concatenateName(int num) {
    std::stringstream ss;
    ss << "S" << num;
    return ss.str();
}

void DFAmini::sortDFA(vector<vector<DFAState> > *dfa) {

    vector<DFAState> temp;
    for (int i = 0; i < dfa->size(); ++i) {
        for (int j = 0; j < dfa->size() - i - 1; ++j) {
            if ((*dfa)[j][0].id > (*dfa)[j + 1][0].id) {
                temp = (*dfa)[j];
                (*dfa)[j] = (*dfa)[j + 1];
                (*dfa)[j + 1] = temp;
            }
        }
    }

}

void DFAmini::sortDFAmini(vector<vector<DFAminiState> > *dfa) {

    vector<DFAminiState> temp;
    for (int i = 0; i < dfa->size(); ++i) {
        for (int j = 0; j < dfa->size() - i - 1; ++j) {
            if ((*dfa)[j][0].id > (*dfa)[j + 1][0].id) {
                temp = (*dfa)[j];
                (*dfa)[j] = (*dfa)[j + 1];
                (*dfa)[j + 1] = temp;
            }
        }
    }

}

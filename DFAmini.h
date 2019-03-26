//
// Created by sharaf on 19/03/2019.
//

#ifndef PROJECT_DFAMINI_H
#define PROJECT_DFAMINI_H

#include <vector>
#include "models/TokenStateNode.h"
#include "models/DFAState.h"
#include "models/DFAminiState.h"

using namespace std;

class DFAmini {

public:

    DFAmini(): states(2, vector<DFAState>()) {

    }

    vector<vector<DFAminiState> > getMinimizedDFA(vector<vector<DFAState> > dfa);

    void printMinimizedStates();

private:
    vector<vector<DFAState> > states;

    void sortDFA (vector<vector<DFAState> > *dfa);

    void sortDFAmini (vector<vector<DFAminiState> > *dfa);

    void getZeroEquivalent(vector<vector<DFAState> > dfa);

    bool isEquivalentStates(vector<vector<DFAState> > dfa, int stateA, int stateB);

    bool isInSameClass(int stateA, int stateB);

    vector<vector<DFAminiState> > renameStates(vector<vector<DFAState> > dfa);

    string concatenateName(int num);

};


#endif //PROJECT_DFAMINI_H

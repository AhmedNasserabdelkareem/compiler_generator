//
// Created by sharaf on 19/03/2019.
//

#ifndef PROJECT_DFAMINI_H
#define PROJECT_DFAMINI_H

#include <vector>
#include "models/TokenStateNode.h"

using namespace std;

class DFAmini {

public:

    DFAmini(): states(2, vector<TokenStateNode>()) {

    }

    vector<vector<TokenStateNode> > getMinimizedDFA(vector<vector<TokenStateNode> > dfa);

    void printMinimizedStates();

private:
    vector<vector<TokenStateNode> > states;

    void getZeroEquivalent(vector<vector<TokenStateNode> > dfa);

    bool isEquivalentStates(vector<vector<TokenStateNode> > dfa, int stateA, int stateB);

    bool isInSameClass(int stateA, int stateB);

    vector<vector<TokenStateNode> > renameStates(vector<vector<TokenStateNode> > dfa);

    string concatenateName(int num);

};


#endif //PROJECT_DFAMINI_H

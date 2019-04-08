//
// Created by ahmed on 25/03/19.
//

#include <models/RulesParser.h>
#include "Controller.h"
#include "NFABuilder.h"

Controller::Controller(string x){
    rules = x;
}

void Controller::start() {
    RulesParser parser(rules);
    parser.init();
    auto *nfaBuilder = new NFABuilder(*new RegularDefinitions(parser.getExp()),
                                      *new RegularExpressions(parser.getDef()));

    printNodes(&nfaBuilder->initialNode, new unordered_set<int>());

    //TODO  NASSER THERE IS A PROBLEM HERE COMMENT TO TEST
  /*  TokenStateNode initialNode = nfaBuilder->getInitialNFANode();

    DFABuilder *dfaBuilder = new DFABuilder(initialNode, nfaBuilder->charactersSet);
    vector<vector<DFAState*>> dfa = dfaBuilder->getDFA();

    DFAmini *dfaMini = new DFAmini();
    dfaMini->getMinimizedDFA(dfa);*/


}

void Controller::printNodes(TokenStateNode *pNode, unordered_set<int> *visitedStates) {

    if (visitedStates->find(pNode->id) != visitedStates->end())
        return;

    cout << "id: " << pNode->id << "[";
    visitedStates->insert(pNode->id);

    for (const auto &statePair: pNode->nextStates) {

        cout << statePair.first << " -> (";
        for (const auto &state:statePair.second) {
            cout << state->id << ", ";
        }
        cout << "), ";
    }
    cout << "]" << endl;

    for (const auto &statePair: pNode->nextStates) {
        for (auto state:statePair.second) {

            printNodes(state, visitedStates);

        }
    }
}


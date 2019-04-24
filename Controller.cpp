//
// Created by ahmed on 25/03/19.
//

#include <models/RulesParser.h>
#include "Controller.h"
#include "NFABuilder.h"
#include "DFABuilder.h"
#include "DFAmini.h"
#include "TokenGenerator.h"

Controller::Controller(string x) {
    rules = x;
}

void Controller::start() {
    RulesParser parser(rules);
    parser.init();
    cout << "enter nfa" << endl;
    auto *nfaBuilder = new NFABuilder(*new RegularDefinitions(parser.getExp()),
                                      *new RegularExpressions(parser.getDef()));

    TokenStateNode initialNode = nfaBuilder->getInitialNFANode();

//    printAcceptingStates(&initialNode, new unordered_set<int>());
 //   printNodes(&initialNode, new unordered_set<int>());

    cout << "enter DFA" << endl;
    DFABuilder *dfaBuilder = new DFABuilder(initialNode, nfaBuilder->charactersSet);
    vector<vector<DFAState>> dfa = dfaBuilder->getDFA();

    cout << "enter mini" << endl;

    DFAmini *dfaMini = new DFAmini();

//    for (int j = 0; j < dfa.size(); ++j) {
//        for (int i = 0; i < dfa[j].size(); ++i) {
//            cout << dfa[j][i].id << " ";
//        }
//        cout << endl;
//    }

    vector<vector<DFAminiState>> minimizedDFA = dfaMini->getMinimizedDFA(dfa);

    cout << minimizedDFA.size() << endl;
//    dfaMini->printMinimizedStates();
//    for (int j = 0; j < dfa.size(); ++j) {
//        for (int i = 0; i < dfa[j].size(); ++i) {
//            cout << minimizedDFA[j][i].stateName << " ";
//        }
//        cout << endl << endl;
//    }

    cout << "enter tokengenerator" << endl;
    TokenGenerator tokenGenerator = TokenGenerator(minimizedDFA, nfaBuilder->charactersSet, parser.getPunc(),

                                                   parser.getKeywrds());
    ifstream program;
    program.open("../input/test_2.txt");
    string pg((std::istreambuf_iterator<char>(program)),
                       std::istreambuf_iterator<char>());

//    cout << endl << pg << endl;

    //TODO write into file
    cout << "Byte code: " << endl;
    vector<string> temp = tokenGenerator.generateTokens(pg);
//    for (int i = 0; i < temp.size(); ++i) {
//        cout << temp[i] << endl;
//    }

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

void Controller::printAcceptingStates(TokenStateNode *pNode, unordered_set<int> *visitedStates) {
    if (visitedStates->find(pNode->id) != visitedStates->end())
        return;

    if (pNode->isAccepting)cout << "id: " << pNode->id << " name: " << pNode->stateName << endl;

    visitedStates->insert(pNode->id);

    for (const auto &statePair: pNode->nextStates) {
        for (auto state:statePair.second) {

            printAcceptingStates(state, visitedStates);

        }
    }
}


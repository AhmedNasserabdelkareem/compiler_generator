#include <iostream>
#include <models/RulesParser.h>
#include <regex>
#include <models/TokenStateNode.h>
#include <DFAmini.h>
#include "Controller.h"
#include "DFABuilder.h"

using namespace std;
void sharafTest();

void husseinTest();

int main() {
    string rules = "../input/rules.txt";
    string test = "../input/test.txt";
//    Controller controller(rules);
//    controller.start();


//    RulesParser parser (rules);
//    parser.init();
//
//    sharafTest();

    husseinTest();

    return 0;
}

void husseinTest() {
    TokenStateNode a = TokenStateNode("A", false);
    TokenStateNode b = TokenStateNode("B", false);
    TokenStateNode c = TokenStateNode("C", true);

    TokenStateNode d = TokenStateNode("D", true);
    TokenStateNode e = TokenStateNode("E", true);

    a.addNextState('x', &b);
    a.addNextState('x', &a);
    a.addNextState('y', &c);
    b.addNextState('x', &c);


//    a.addNextState(RegularExpressions::LAMBDA, &b);
//    a.addNextState(RegularExpressions::LAMBDA, &c);
//    b.addNextState(RegularExpressions::LAMBDA, &d);
//    b.addNextState(RegularExpressions::LAMBDA, &c);
//    d.addNextState(RegularExpressions::LAMBDA, &e);

    TokenStateNode initialNode = a;
    set<char> charactersSet;
    charactersSet.insert('x');
    charactersSet.insert('y');
    DFABuilder *dfaBuilder = new DFABuilder(initialNode, charactersSet);
//    DFAState * result = dfaBuilder->getDFAInitialNode();
    vector<vector<DFAState*>> dfa = dfaBuilder->getDFA();

}

void sharafTest(){
//
//    TokenStateNode *tt = new TokenStateNode("A", true);
//    TokenStateNode *ff = new TokenStateNode("B", false);
//
//    vector<TokenStateNode *> tv(1, tt);
//    vector<TokenStateNode *> fv(1, ff);
//
//    DFAState a = DFAState(fv, 0);
//    DFAState b = DFAState(fv, 3);
//    DFAState c = DFAState(tv, 2);
//    DFAState d = DFAState(tv, 1);
//    DFAState e = DFAState(tv, 4);
//    DFAState f = DFAState(fv, 5);
//
//    vector<vector<DFAState> > states(6, vector<DFAState>());
//    states[0].push_back(a);
//    states[0].push_back(b);
//    states[0].push_back(c);
//
//    states[1].push_back(b);
//    states[1].push_back(a);
//    states[1].push_back(d);
//
//    states[2].push_back(c);
//    states[2].push_back(e);
//    states[2].push_back(f);
//
//    states[3].push_back(d);
//    states[3].push_back(e);
//    states[3].push_back(f);
//
//    states[4].push_back(e);
//    states[4].push_back(e);
//    states[4].push_back(f);
//
//    states[5].push_back(f);
//    states[5].push_back(f);
//    states[5].push_back(f);
//
//    cout << "   0 1" << endl;
//    cout << "  -----" << endl;
//    for (int i = 0; i < states.size(); ++i) {
//        for (int j = 0; j < states[0].size(); ++j) {
//            cout << states[i][j].id;
//            if (j == 0)
//                cout << "|";
//
//            cout << " ";
//        }
//        cout << endl;
//    }
//
//    DFAmini mini;
//    vector<vector<DFAminiState> >newStatesn = mini.getMinimizedDFA(states);
//    mini.printMinimizedStates();
//
//    cout << endl;
//    cout << "      0   1" << endl;
//    cout << "    -------" << endl;
//    for (int i = 0; i < newStatesn.size(); ++i) {
//        for (int j = 0; j < newStatesn[0].size(); ++j) {
//            cout << newStatesn[i][j].stateName + " ";
//            if (j == 0)
//                cout << "|";
//
//            cout << " ";
//        }
//        cout << endl;
//    }
}
#include <iostream>
#include <models/RulesParser.h>
#include <regex>
#include <models/TokenStateNode.h>
#include <DFAmini.h>
#include "Controller.h"

using namespace std;
void sharafTest();

int main() {
    string rules = "../input/rules.txt";
    string test = "../input/test.txt";
    Controller controller(rules);
    controller.start();


    RulesParser parser (rules);
    parser.init();

    sharafTest();

    return 0;
}

void sharafTest(){
    TokenStateNode a = TokenStateNode("A", false);
    TokenStateNode b = TokenStateNode("B", false);
    TokenStateNode c = TokenStateNode("C", true);
    TokenStateNode d = TokenStateNode("D", true);
    TokenStateNode e = TokenStateNode("E", true);
    TokenStateNode f = TokenStateNode("F", false);

    vector<vector<TokenStateNode> > states(6, vector<TokenStateNode>());
    states[0].push_back(a);
    states[0].push_back(b);
    states[0].push_back(c);

    states[1].push_back(b);
    states[1].push_back(a);
    states[1].push_back(d);

    states[2].push_back(c);
    states[2].push_back(e);
    states[2].push_back(f);

    states[3].push_back(d);
    states[3].push_back(e);
    states[3].push_back(f);

    states[4].push_back(e);
    states[4].push_back(e);
    states[4].push_back(f);

    states[5].push_back(f);
    states[5].push_back(f);
    states[5].push_back(f);

    cout << "    0  1" << endl;
    cout << "   -----" << endl;
    for (int i = 0; i < states.size(); ++i) {
        for (int j = 0; j < states[0].size(); ++j) {
            cout << states[i][j].stateName + " ";
            if (j == 0)
                cout << "|";

            cout << " ";
        }
        cout << endl;
    }

    DFAmini mini;
    states = mini.getMinimizedDFA(states);
    mini.printMinimizedStates();

    cout << endl;
    cout << "      0   1" << endl;
    cout << "    -------" << endl;
    for (int i = 0; i < states.size(); ++i) {
        for (int j = 0; j < states[0].size(); ++j) {
            cout << states[i][j].stateName + " ";
            if (j == 0)
                cout << "|";

            cout << " ";
        }
        cout << endl;
    }
}
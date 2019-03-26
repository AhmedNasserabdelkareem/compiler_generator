//
// Created by ahmed on 25/03/19.
//

#include <models/RulesParser.h>
#include "Controller.h"
#include "NFABuilder.h"
#include "DFABuilder.h"
#include "DFAmini.h"

Controller::Controller(string x){
    rules = x;
}

void Controller::start() {
    RulesParser parser(rules);
    parser.init();
/*   cout<<"EXP"<<r->expressionsRanges.size()<<endl;
    for (auto& it: r->expressionsRanges) {
        cout << it.first<<" : "<<it.second<<" "<<endl;
    }*/
    NFABuilder *nfaBuilder = new NFABuilder(*new RegularDefinitions(parser.getExp()),*new RegularExpressions(parser.getDef()));
    TokenStateNode initialNode = nfaBuilder->getInitialNFANode();

    DFABuilder *dfaBuilder = new DFABuilder(initialNode, nfaBuilder->charactersSet);
    vector<vector<DFAState*>> dfa = dfaBuilder->getDFA();

    DFAmini *dfaMini = new DFAmini();
    dfaMini->getMinimizedDFA(dfa);


}
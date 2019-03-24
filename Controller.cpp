//
// Created by ahmed on 25/03/19.
//

#include <models/RulesParser.h>
#include "Controller.h"
#include "NFABuilder.h"
#include "DFABuilder.h"

Controller::Controller(string x){
    rules = x;
}

void Controller::start() {
    RulesParser parser(rules);
    parser.init();

    NFABuilder *nfaBuilder = new NFABuilder(new RegularDefinitions(),new RegularExpressions());
    TokenStateNode initialNode = nfaBuilder->getInitialNFANode();

    DFABuilder *dfaBuilder = new DFABuilder(initialNode);
    vector<vector<DFAState*>> dfa = dfaBuilder->getDFA();



}
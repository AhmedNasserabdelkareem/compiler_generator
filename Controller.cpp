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
    NFABuilder *nfaBuilder = new NFABuilder(*new RegularDefinitions(parser.getExp()),*new RegularExpressions(parser.getDef()));
    //TODO  NASSER THERE IS A PROBLEM HERE COMMENT TO TEST
  /*  TokenStateNode initialNode = nfaBuilder->getInitialNFANode();

    DFABuilder *dfaBuilder = new DFABuilder(initialNode, nfaBuilder->charactersSet);
    vector<vector<DFAState*>> dfa = dfaBuilder->getDFA();

    DFAmini *dfaMini = new DFAmini();
    dfaMini->getMinimizedDFA(dfa);*/


}
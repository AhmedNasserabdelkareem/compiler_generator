//
// Created by Bassam on 3/19/2019.
//

#include "NFABuilder.h"

NFABuilder::NFABuilder(const RegularDefinitions &regularDefinitions, const RegularExpressions &regularExpressions)
        : regularDefinitions(regularDefinitions), regularExpressions(regularExpressions) {
    buildNFATree();
}

TokenStateNode NFABuilder::getInitialNFANode() {
    return initialNode;
}

void NFABuilder::buildNFATree() {

}

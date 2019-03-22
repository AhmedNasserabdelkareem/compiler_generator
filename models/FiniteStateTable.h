//
// Created by Bassam on 3/22/2019.
//

#ifndef COMPILER_GENERATOR_MASTER_NFATABLE_H
#define COMPILER_GENERATOR_MASTER_NFATABLE_H

#include <deque>
#include "TokenStateNode.h"
#include "RegularExpressions.h"

class FiniteStateTable {

public:
    deque<TokenStateNode *> statesDequeue;
};


#endif //COMPILER_GENERATOR_MASTER_NFATABLE_H

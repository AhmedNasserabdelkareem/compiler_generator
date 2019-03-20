//
// Created by Bassam on 3/19/2019.
//

#ifndef LEXICAL_ANALYZER_TOKENS_H
#define LEXICAL_ANALYZER_TOKENS_H

#include <unordered_set>

using namespace std;

class Keywords {

public:
    unordered_set<string> keywords;
    unordered_set<string> conditionalKeywords;
    unordered_set<string> dataTypes;
};


#endif //LEXICAL_ANALYZER_TOKENS_H

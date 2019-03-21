//
// Created by Bassam on 3/19/2019.
//

#ifndef LEXICAL_ANALYZER_PUNCTUATION_H
#define LEXICAL_ANALYZER_PUNCTUATION_H

#include <unordered_set>

using namespace std;

class Punctuations {

public:
    unordered_set<string> punctuations;

    Punctuations(const unordered_set<string> &punctuations);
};


#endif //LEXICAL_ANALYZER_PUNCTUATION_H

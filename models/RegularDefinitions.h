//
// Created by Bassam on 3/19/2019.
//

#ifndef LEXICAL_ANALYZER_REGULARDEFINITIONS_H
#define LEXICAL_ANALYZER_REGULARDEFINITIONS_H

#include <unordered_map>
#include <vector>

using namespace std;


class RegularDefinitions {
public:
    RegularDefinitions(const unordered_map<string, string> &definitions);

public:
    static unordered_map<string, string> definitions;

};


#endif //LEXICAL_ANALYZER_REGULARDEFINITIONS_H

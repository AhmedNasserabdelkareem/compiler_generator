//
// Created by Ahmednasser on 3/20/2019.
//

#ifndef COMPILER_GENERATOR_RULESPARSER_H
#define COMPILER_GENERATOR_RULESPARSER_H

#include <string>
#include <fstream>
#include <vector>
#include "Punctuations.h"
#include "Keywords.h"
#include "RegularExpressions.h"
#include "RegularDefinitions.h"

class RulesParser {
public:
    RulesParser(string input);
    vector<string> lines;
    unordered_map<string, string> def;

    const unordered_map<string, string> &getDef() const;

    const unordered_map<string, string> &getExp() const;

    const unordered_set<string> &getPunc() const;

    const unordered_set<string> &getKeywrds() const;

    unordered_map<string, string> exp;
    unordered_set<string> punc;
    unordered_set<string> keywrds;

    void init();

private:
    std::string rulesFile;
    ifstream streamfile;
    void readFile();
    void fillData();
    int recognizeType(string line);
    void insertData(string line,int Type);
    void getArgfromRD(string line);
    void getArgfromRE(string line);
    void getArgfromPN(string line);
    void getArgfromKW(string line);
    vector<string> splitString (string line,char delimiter);

};


#endif //COMPILER_GENERATOR_RULESPARSER_H

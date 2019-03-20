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
    Punctuations punc;
    Keywords keywords;
    RegularExpressions regexpression;
    RegularDefinitions regdefenition;
    vector<string> lines;
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

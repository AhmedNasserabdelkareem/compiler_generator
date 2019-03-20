//
// Created by Ahmednasser on 3/20/2019.
//

#include <iostream>
#include <regex>
#include "RulesParser.h"
#include "Types.h"
RulesParser::RulesParser(string input) {rulesFile=input;}
void RulesParser::init() {
    readFile();
    fillData();
}
void RulesParser::readFile() {
    streamfile.open(rulesFile);
    string line;
    while (getline(streamfile, line)){
    lines.push_back(line);
    }
    streamfile.close();
}

void RulesParser::fillData() {
    for( int i=0;i<lines.size();i++){
       insertData(lines[i],recognizeType(lines[i]));
    }

}
int RulesParser::recognizeType(string line) {
    line=regex_replace(line,regex("\\s"), "");
    if(line.find_first_of(':')!=string::npos){
        int pos = line.find_first_of(':');
        if(line[pos-1]!='\\'){
            return REGULAREXPRESSION;
        }
    }

    if(line.find_first_of('=')!=string::npos){
        int pos = line.find_first_of('=');
        if(line[pos-1]!='\\'){
            return REGULARDEFINITION;
        }
    }
    if(line.find_first_of('[')!=string::npos){
        int pos = line.find_first_of('[');
        if(line[pos]!=-1){
            return PUNCTUATION;
        }
    }

    if(line.find_first_of('{')!=string::npos){
        int pos = line.find_first_of('{');
        if(line[pos]!=-1){
            return KEYWORD;
        }
    }
    return -1;
}
void RulesParser::insertData(string line, int Type) {
    switch (Type){
        case REGULARDEFINITION:
            getArgfromRD(line);
            break;
        case REGULAREXPRESSION:
            getArgfromRE(line);
            break;
        case PUNCTUATION:
            getArgfromPN(line);
            break;
        case KEYWORD:
            getArgfromKW(line);
            break;
    }

}
void RulesParser::getArgfromKW(string line) {
/*
if(line[0]!='{'){
    int pos = line.find_first_of('{');
    line=line.erase(pos,pos+1);

}
if(line[line.size()-1]!='}'){
    int pos = line.find_last_of('}');
    line=line.erase(pos-1,line.size()-1);
}
*/

}
void RulesParser::getArgfromPN(string line) {

}
void RulesParser::getArgfromRD(string line) {
    line=regex_replace(line,regex("\\s"), "");
    vector<string> result =splitString(line,'=');
    if (result.size()==2){
        RegularDefinitions::definitions.insert(result[0],result[1]);
    }
}
void RulesParser::getArgfromRE(string line) {
    line=regex_replace(line,regex("\\s"), "");
    vector<string> result =splitString(line,':');
    if (result.size()==2){
        RegularDefinitions::definitions.insert(result[0],result[1]);
    }
}
vector<string> RulesParser::splitString(string line,char delimiter) {
    vector<string> temp;
    std::stringstream ss(line);
    std::string in;
    while (std::getline(ss, in, delimiter)) {
        temp.push_back(in);
    }
    return temp;
}

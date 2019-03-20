#include <iostream>
#include <models/RulesParser.h>
#include <regex>

using namespace std;

/*vector<string> splitString(string line,char delimiter) {
    vector<string> temp;
    std::stringstream ss(line);
    std::string in;
    while (std::getline(ss, in, delimiter)) {
        temp.push_back(in);
    }
    return temp;
}*/

int main() {
    string rules = "../input/rules.txt";
    string test = "../input/test.txt";
    // RulesParser parser (rules);
    // parser.init();
 /*   string x ="letter = a-z | A-Z";
    // string y ="relop: \=\= | !\= | > | >\= | < | <\=";
    //string z= "[== , \( \) { }]";
    string t=" { if else while } ";
    string line = t;
    if(line[0]!='{'){
        int pos = line.find_first_of('{');
        line=line.erase(pos,pos+1);

    }
    if(line[line.size()-1]!='}'){
        int pos = line.find_last_of('}');
        line=line.erase(pos-1,line.size()-1);
    }
    cout<<line;
    vector<string> tmp = splitString(line,' ');
    for(int i=0;i<tmp.size();i++) {
        Keywords::keywords.insert(tmp[i]);
        cout<<tmp[i]<<endl;
    }

*//*    vector<string> te = splitString(x,'=');
    cout<<te.size()<<endl;
    for(int i=0;i<te.size();i++){
        cout<<te[i]<<endl;
    }*/

    return 0;
}
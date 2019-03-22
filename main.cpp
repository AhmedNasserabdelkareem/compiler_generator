#include <iostream>
#include <models/RulesParser.h>
#include <regex>
#include <models/TokenStateNode.h>
#include <DFAmini.h>
#include <RegularDefinitions.h>
static const char KLEENE_CLOSURE = '*', POSITIVE_CLOSURE = '+',
        UNION = '|', CONCATENATION = 8, OPENING_BRACKET = '(', CLOSING_BRACKET = ')',EXPONENT = 'E',DOT ='.';

static const string LAMBDA;

using namespace std;
void sharafTest();
void tokenizeTest(string x);
int smallestkeylength (unordered_map<string, string> definitions);
bool checkKeys(unordered_map<string, string> definitions,string x);
char getChar(char x);
int main() {
    string rules = "../input/rules.txt";
    string test = "../input/test.txt";
    RulesParser parser (rules);
    parser.init();
/*    vector <string> c =StringUtils::split(x,' ');
    for (int i = 0; i < c.size(); ++i) {
        cout<<c[i]<<c[i].size()<<endl;
    }*/
/*    std::
    ss << 4.5 << ", " << 4 << " whatever";
    std::string str = ss.str();
    cout<<str;*/

   // sharafTest();
    string x =" digit+ | digit+ . digit ( \\L | E digit)";
tokenizeTest(x);
    return 0;
}

void sharafTest(){
    TokenStateNode a = TokenStateNode("A", false);
    TokenStateNode b = TokenStateNode("B", false);
    TokenStateNode c = TokenStateNode("C", true);
    TokenStateNode d = TokenStateNode("D", true);
    TokenStateNode e = TokenStateNode("E", true);
    TokenStateNode f = TokenStateNode("F", false);

    vector<vector<TokenStateNode> > states(6, vector<TokenStateNode>());
    states[0].push_back(a);
    states[0].push_back(b);
    states[0].push_back(c);

    states[1].push_back(b);
    states[1].push_back(a);
    states[1].push_back(d);

    states[2].push_back(c);
    states[2].push_back(e);
    states[2].push_back(f);

    states[3].push_back(d);
    states[3].push_back(e);
    states[3].push_back(f);

    states[4].push_back(e);
    states[4].push_back(e);
    states[4].push_back(f);

    states[5].push_back(f);
    states[5].push_back(f);
    states[5].push_back(f);

    cout << "    0  1" << endl;
    cout << "   -----" << endl;
    for (int i = 0; i < states.size(); ++i) {
        for (int j = 0; j < states[0].size(); ++j) {
            cout << states[i][j].stateName + " ";
            if (j == 0)
                cout << "|";

            cout << " ";
        }
        cout << endl;
    }

    DFAmini mini;
    states = mini.getMinimizedDFA(states);
    mini.printMinimizedStates();

    cout << endl;
    cout << "      0   1" << endl;
    cout << "    -------" << endl;
    for (int i = 0; i < states.size(); ++i) {
        for (int j = 0; j < states[0].size(); ++j) {
            cout << states[i][j].stateName + " ";
            if (j == 0)
                cout << "|";

            cout << " ";
        }
        cout << endl;
    }
}
void tokenizeTest(string x){
    unordered_map<string, string> definitions;
    bool flag1=0,flag2=0,flag3=0;
    vector<string> result ;
    definitions.insert(make_pair("letter","a-z"));
    definitions.insert(make_pair("digit","0-9"));
    stringstream ss;
    int smallLength = smallestkeylength(definitions);
    int i=0;
    while(i<x.size()){
        char tmp = x[i];
        if(x[i]==' '){
            i++;
            continue;
        }
        if(isalpha(x[i])&&x[i]!='E'&&x[i]!='L'){
            string temp = x.substr(i,smallLength);
            if(checkKeys(definitions,temp)){
                result.push_back(temp);
                i+=smallLength;
                flag1=1;
            }
        }
        if(x[i]=='+'||x[i]=='*'||x[i]=='|'||x[i]=='.'||x[i]=='('||x[i]==')'||x[i]=='E'){
            char out = getChar(x[i]);
            result.push_back(string(1,out));
            i++;
            flag2=1;
        }
        if(x[i]=='\\'&&x[i+1]=='L'){
            string temp = x.substr(i,2);
            result.push_back(LAMBDA);
            i+=2;
            flag3=1;
        }
if(!(flag1||flag2||flag3)){
    i++;
    }
        flag1=0,flag2=0,flag3=0;
    }
    for (int i = 0; i < result.size(); ++i) {
        cout<<result[i]<<result[i].size()<<endl;
    }
  //  cout<<isalpha('E')<<isalpha('\\')<<isalpha('.')<<isalpha('|');

}
int smallestkeylength (unordered_map<string, string> definitions){
    int min=1000;
    for (auto& it: definitions) {
        if(it.first.size()<min){
            min=it.first.size();
        }
    }
    return min;
}
bool checkKeys(unordered_map<string, string> definitions,string x){
    for (auto& it: definitions) {
        if(it.first.compare(x)==0){
            return true;
        }
    }
    return false;
}
char getChar(char x){
    switch (x){
        case '*':
            return KLEENE_CLOSURE;
        case '+':
            return POSITIVE_CLOSURE;
        case '|':
            return UNION;
        case '.':
            return DOT;
        case 'E':
            return EXPONENT;
        case '(':
            return OPENING_BRACKET;
        case ')' :
            return CLOSING_BRACKET;
    }

}
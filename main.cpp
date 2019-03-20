#include <iostream>
#include <models/RulesParser.h>
#include <regex>

using namespace std;

int main() {
string rules = "../input/rules.txt";
string test = "../input/test.txt";
   RulesParser parser (rules);
    parser.init();

    return 0;
}
//
// Created by Bassam on 3/19/2019.
//

#include <iostream>
#include "RegularDefinitions.h"

const string RegularDefinitions::LAMBDA = "\\L";

RegularDefinitions::RegularDefinitions(const unordered_map<string, string> &definitions) : definitions(definitions) {
/*    cout<<"EXP"<<definitions.size()<<endl;
    for (auto& it: definitions) {
        cout << it.first<<" : "<<it.second<<" "<<endl;
    }*/
}

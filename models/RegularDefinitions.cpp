//
// Created by Bassam on 3/19/2019.
//

#include <iostream>
#include "RegularDefinitions.h"

RegularDefinitions::RegularDefinitions(const unordered_map<string, string> &definitions) : definitions(definitions) {
/*  cout<<"DEFINITIONS"<<definitions.size()<<endl;
   for (auto& it: definitions) {
        cout << it.first<<" : "<<it.second<<endl;
    }*/
}

//
// Created by sharaf on 26/03/2019.
//

#ifndef COMPILER_GENERATOR_MASTER_DFAMINISTATE_H
#define COMPILER_GENERATOR_MASTER_DFAMINISTATE_H

#include <string>

using namespace std;

class DFAminiState {
public:

    DFAminiState();

    DFAminiState(string name, bool accept, int id, string token);

public:
    int id;
    bool isAccepting;
    string stateName; //Equivalent to the definition name when it's an accepting state
    string token;
};


#endif //COMPILER_GENERATOR_MASTER_DFAMINISTATE_H

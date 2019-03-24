//
// Created by ahmed on 25/03/19.
//

#ifndef COMPILER_GENERATOR_MASTER_CONTROLLER_H
#define COMPILER_GENERATOR_MASTER_CONTROLLER_H

#include <iostream>
using namespace std;

class Controller {
public:
    Controller(string rules);
    void start();


private:
    string rules;
};


#endif //COMPILER_GENERATOR_MASTER_CONTROLLER_H

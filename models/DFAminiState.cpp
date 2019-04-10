//
// Created by sharaf on 26/03/2019.
//

#include "DFAminiState.h"

DFAminiState::DFAminiState(){}

DFAminiState::DFAminiState(string name, bool accept, int id, string token) : stateName(name), isAccepting(accept),
                                                                             id(id), token(token) {}

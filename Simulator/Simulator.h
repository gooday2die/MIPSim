//
// @file : Simulator.h
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : A file that defines all attributes and member functions for class Simulator
//

#ifndef MIPSIM_SIMULATOR_H
#define MIPSIM_SIMULATOR_H
#pragma once

#include <iostream>
#include <map>
#include <string>

#include "../defines.h"
#include "RegisterHandler.h"
#include "MachineCodeSimulator.h"
#include "Signals.h"

using namespace std;

/**
 * A class for simulating machine codes
 */
class Simulator {
private:
    RegisterHandler* registerHandler = new RegisterHandler();
    MachineCodeSimulator machineCodeSimulator = MachineCodeSimulator(registerHandler);
    uint32_t* textSection;
public:
    Simulator(map<string, uint32_t*>);
    uint32_t* getRegister(int);
    void executeMachineCode(uint32_t);
    void printAllRegisters();
    void run();
};


#endif //MIPSIM_SIMULATOR_H

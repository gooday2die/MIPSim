//
// @file : Simulator.h
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : A file that defines all attributes and member functions for class Simulator
// @date: 2022-03-07

#ifndef MIPSIM_SIMULATOR_H
#define MIPSIM_SIMULATOR_H
#pragma once

#include <iostream>

#include "../defines.h"
#include "RegisterHandler.h"
#include "../MachineCodes/MachineCodeSimulator.h"

class Simulator {
private:
    RegisterHandler registerHandler = RegisterHandler();
    MachineCodeSimulator machineCodeSimulator = MachineCodeSimulator(registerHandler);
    uint32_t* branches;
    uint32_t* memory;
public:
    Simulator(uint32_t*, uint32_t*);
    uint32_t* getRegister(int);
    void executeMachineCode(uint32_t);
    void printAllRegisters();
    void run();
};


#endif //MIPSIM_SIMULATOR_H

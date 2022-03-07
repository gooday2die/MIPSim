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
#include "../Register/RegisterHandler.h"
#include "../MachineCodes/MachineCodeSimulator.h"

class Simulator {
private:
    RegisterHandler registerHandler = RegisterHandler();
    MachineCodeSimulator machineCodeSimulator = MachineCodeSimulator(registerHandler);
    void tester();
public:
    Simulator();
};


#endif //MIPSIM_SIMULATOR_H

//
// @file : MachineCodeSimulator.h
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : A file that defines all attributes and member functions for class MachineCodeSimulator
//

#ifndef MIPSIM_MACHINECODESIMULATOR_H
#define MIPSIM_MACHINECODESIMULATOR_H
#pragma once

#include "RegisterHandler.h"
#include "Instructions.h"


class MachineCodeSimulator {
private:
    RegisterHandler* registerHandler;
public:
    MachineCodeSimulator(RegisterHandler*);
    void executeCode(uint32_t);
};


#endif //MIPSIM_MACHINECODESIMULATOR_H

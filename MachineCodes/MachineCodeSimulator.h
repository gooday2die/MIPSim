//
// @file : MachineCodeSimulator.h
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : A file that defines all attributes and member functions for class MachineCodeSimulator
// @date: 2022-03-07

#ifndef MIPSIM_MACHINECODESIMULATOR_H
#define MIPSIM_MACHINECODESIMULATOR_H
#pragma once

#include "../Simulator/RegisterHandler.h"
#include "../Instructions/Instructions.h"


class MachineCodeSimulator {
private:
    RegisterHandler registerHandler;
    uint32_t* branches;
    uint16_t branchCount;
public:
    MachineCodeSimulator(RegisterHandler);
    void executeCode(uint32_t);
    uint16_t getBranchCount();
    void setBranches(uint32_t*);
};


#endif //MIPSIM_MACHINECODESIMULATOR_H

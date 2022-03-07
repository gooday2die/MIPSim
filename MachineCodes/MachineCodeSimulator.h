//
// @file : MachineCodeSimulator.h
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : A file that defines all attributes and member functions for class MachineCodeSimulator
// @date: 2022-03-07

#ifndef MIPSIM_MACHINECODESIMULATOR_H
#define MIPSIM_MACHINECODESIMULATOR_H
#pragma once

#include "MachineCode.h"
#include "../Register/RegisterHandler.h"
#include "../Instructions/Instructions.h"


class MachineCodeSimulator {
private:
    RegisterHandler registerHandler;
public:
    MachineCodeSimulator(RegisterHandler);
    int executeCode(MachineCode);
};


#endif //MIPSIM_MACHINECODESIMULATOR_H

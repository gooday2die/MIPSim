//
// @file : MIPSim.h
// @author : Gooday2die (Isu Kim)
// @Contacts : edina00@naver.com
// @brief : A file that defines all attributes and member functions for class MIPSim
// 

#ifndef MIPSIM2_MIPSIM_H
#define MIPSIM2_MIPSIM_H
#pragma once

#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

#include "./Utils/Expression.h"
#include "./Assembler/Assembler.h"
#include "./Simulator/Simulator.h"

using namespace std;

/**
 * A class for MIPSim
 */
class MIPSim {
private:
    uint32_t* registers = nullptr;
    uint32_t pc;

    Assembler* assembler = nullptr;
    Simulator* simulator = nullptr;

    vector<Expression> textSectionExpressions;
    uint32_t textSectionExpressionCount = 0;

public:
    explicit MIPSim(const string&);
    void assemble();
    void simulate();
    void printRegisters();
};


#endif //MIPSIM2_MIPSIM_H

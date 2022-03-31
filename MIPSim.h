//
// @file : MIPSim.h
// @author : Gooday2die (Isu Kim)
// @Contacts : edina00@naver.com
// @brief : 
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

using namespace std;

/**
 * A class for MIPSim
 */
class MIPSim {
private:
    uint32_t* registers = nullptr;
    uint32_t pc;

    Assembler* assembler = nullptr;

    string fileName;
    vector<Expression> textSectionExpressions;
    uint32_t textSectionExpressionCount = 0;

public:
    explicit MIPSim(const string&);
    void assemble();
};


#endif //MIPSIM2_MIPSIM_H

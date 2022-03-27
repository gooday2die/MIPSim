//
// @file : Instruction.
// @author : Gooday2die (Isu Kim)
// @Contacts : edina00@naver.com
// @brief : 
//

#ifndef MIPSIM2_INSTRUCTION_H
#define MIPSIM2_INSTRUCTION_H
#pragma once

#include <vector>
#include "Signals.h"

using namespace std;

class Instruction {
public:
    vector<uint32_t*> parameters;
    explicit Instruction(const vector<uint32_t*>&);
    virtual void execute() = 0;
};

class addu_ : public Instruction {
public:
    explicit addu_(const vector<uint32_t*>& argParameters) : Instruction(argParameters){};
    void execute() override;
};

class syscall_ : public Instruction{
public:
    explicit syscall_(const vector<uint32_t*>& argParameters) : Instruction(argParameters){};
    void execute() override;
};

#endif //MIPSIM2_INSTRUCTION_H

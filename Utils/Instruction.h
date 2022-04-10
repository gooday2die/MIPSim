//
// @file : Instruction.h
// @author : Gooday2die (Isu Kim)
// @Contacts : edina00@naver.com
// @brief : A file that defines all attributes and member functions for class Instruction
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

class add_ : public Instruction {
public:
    explicit add_(const vector<uint32_t*>& argParameters) : Instruction(argParameters){};
    void execute() override;
};

class addu_ : public Instruction {
public:
    explicit addu_(const vector<uint32_t*>& argParameters) : Instruction(argParameters){};
    void execute() override;
};

class and_ : public Instruction {
public:
    explicit and_(const vector<uint32_t*>& argParameters) : Instruction(argParameters){};
    void execute() override;
};

class addi_ : public Instruction {
public:
    explicit addi_(const vector<uint32_t*>& argParameters) : Instruction(argParameters){};
    void execute() override;
};

class addiu_ : public Instruction {
public:
    explicit addiu_(const vector<uint32_t*>& argParameters) : Instruction(argParameters){};
    void execute() override;
};

class andi_ : public Instruction {
public:
    explicit andi_(const vector<uint32_t*>& argParameters) : Instruction(argParameters){};
    void execute() override;
};

class nor_ : public Instruction {
public:
    explicit nor_(const vector<uint32_t*>& argParameters) : Instruction(argParameters){};
    void execute() override;
};

class or_ : public Instruction {
public:
    explicit or_(const vector<uint32_t*>& argParameters) : Instruction(argParameters){};
    void execute() override;
};

class ori_ : public Instruction {
public:
    explicit ori_(const vector<uint32_t*>& argParameters) : Instruction(argParameters){};
    void execute() override;
};

class slt_ : public Instruction {
public:
    explicit slt_(const vector<uint32_t*>& argParameters) : Instruction(argParameters){};
    void execute() override;
};

class slti_ : public Instruction {
public:
    explicit slti_(const vector<uint32_t*>& argParameters) : Instruction(argParameters){};
    void execute() override;
};

class sltiu_ : public Instruction {
public:
    explicit sltiu_(const vector<uint32_t*>& argParameters) : Instruction(argParameters){};
    void execute() override;
};

class sltu_ : public Instruction {
public:
    explicit sltu_(const vector<uint32_t*>& argParameters) : Instruction(argParameters){};
    void execute() override;
};

class sub_ : public Instruction {
public:
    explicit sub_(const vector<uint32_t*>& argParameters) : Instruction(argParameters){};
    void execute() override;
};

class subu_ : public Instruction {
public:
    explicit subu_(const vector<uint32_t*>& argParameters) : Instruction(argParameters){};
    void execute() override;
};

class j_ : public Instruction {
public:
    explicit j_(const vector<uint32_t*>& argParameters) : Instruction(argParameters){};
    void execute() override;
};

class jal_ : public Instruction {
public:
    explicit jal_(const vector<uint32_t*>& argParameters) : Instruction(argParameters){};
    void execute() override;
};

class jr_ : public Instruction {
public:
    explicit jr_(const vector<uint32_t*>& argParameters) : Instruction(argParameters){};
    void execute() override;
};

class sll_ : public Instruction {
public:
    explicit sll_(const vector<uint32_t*>& argParameters) : Instruction(argParameters){};
    void execute() override;
};

class srl_ : public Instruction {
public:
    explicit srl_(const vector<uint32_t*>& argParameters) : Instruction(argParameters){};
    void execute() override;
};

class beq_ : public Instruction {
public:
    explicit beq_(const vector<uint32_t*>& argParameters) : Instruction(argParameters){};
    void execute() override;
};

class bne_ : public Instruction {
public:
    explicit bne_(const vector<uint32_t*>& argParameters) : Instruction(argParameters){};
    void execute() override;
};

class syscall_ : public Instruction{
public:
    explicit syscall_(const vector<uint32_t*>& argParameters) : Instruction(argParameters){};
    void execute() override;
};

#endif //MIPSIM2_INSTRUCTION_H

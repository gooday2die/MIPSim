//
// @file : Instruction.
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : 
//

#include "Instruction.h"


Instruction::Instruction(const vector<uint32_t*>& argParameters) {
    this->parameters = argParameters;
}

void add_::execute() {
    uint32_t rs = *Instruction::parameters.at(0);
    uint32_t rt = *Instruction::parameters.at(1);
    uint32_t* rd = Instruction::parameters.at(2);

    if ((rs > 0) && (rt > INT_MAX - rs))
        throw GeneralExceptions::OverflowException();
    else *rd = rs + rt;
}

void addu_::execute() {
    uint32_t rs = *Instruction::parameters.at(0);
    uint32_t rt = *Instruction::parameters.at(1);
    uint32_t* rd = Instruction::parameters.at(2);

    *rd = rs + rt;
}

void and_::execute() {
    uint32_t rs = *Instruction::parameters.at(0);
    uint32_t rt = *Instruction::parameters.at(1);
    uint32_t* rd = Instruction::parameters.at(2);
    *rd = rs & rt;
}

void addi_::execute() {
    uint32_t rs = *Instruction::parameters.at(0);
    uint32_t* rt = Instruction::parameters.at(1);
    uint32_t imm = *Instruction::parameters.at(2);

    if ((rs > 0) && (imm > INT_MAX - rs))
        throw GeneralExceptions::OverflowException();
    else *rt = rs + imm;
}

void addiu_::execute() {
    uint32_t rs = *Instruction::parameters.at(0);
    uint32_t* rt = Instruction::parameters.at(1);
    uint32_t imm = *Instruction::parameters.at(2);
    *rt = rs + imm;
}

void andi_::execute() {
    uint32_t rs = *Instruction::parameters.at(0);
    uint32_t* rt = Instruction::parameters.at(1);
    uint32_t imm = *Instruction::parameters.at(2);
    *rt = rs & imm;
}

void nor_::execute() {
    uint32_t rs = *Instruction::parameters.at(0);
    uint32_t rt = *Instruction::parameters.at(1);
    uint32_t* rd = Instruction::parameters.at(2);
    *rd = ~(rs | rt);
}

void or_::execute() {
    uint32_t rs = *Instruction::parameters.at(0);
    uint32_t rt = *Instruction::parameters.at(1);
    uint32_t* rd = Instruction::parameters.at(2);
    *rd = (rs | rt);
}

void ori_::execute() {
    uint32_t rs = *Instruction::parameters.at(0);
    uint32_t* rt = Instruction::parameters.at(1);
    uint32_t imm = *Instruction::parameters.at(2);
    *rt = rs | imm;
}



void syscall_::execute() {
    uint32_t v0_val = *Instruction::parameters.at(0);
    uint32_t a0_val = *Instruction::parameters.at(1);

    switch(v0_val){
        case 1: // v0 with syscall prints out int in $a0;
            printf("[OUTPUT] %d\n", a0_val);
            return;

        case 10: // v0 with syscall exits program.
            throw Syscall::Exit();
    }
}
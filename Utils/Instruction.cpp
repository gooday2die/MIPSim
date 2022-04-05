//
// @file : Instruction.
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : 
//

#include "Instruction.h"


Instruction::Instruction(const vector<uint32_t*>& argParameters) {
    for (auto argParameter : argParameters){
        this->parameters.emplace_back(argParameter);
    }
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

void slt_::execute() {
    uint32_t rs = *Instruction::parameters.at(0);
    uint32_t rt = *Instruction::parameters.at(1);
    uint32_t* rd = Instruction::parameters.at(2);
    *rd = (signed int)rs < (signed int)rt;
}

void slti_::execute() {
    uint32_t rs = *Instruction::parameters.at(0);
    uint32_t* rt = Instruction::parameters.at(1);
    uint32_t imm = *Instruction::parameters.at(2);
    *rt = (signed int)rs < (signed int) imm;
}

void sltiu_::execute() {
    uint32_t rs = *Instruction::parameters.at(0);
    uint32_t* rt = Instruction::parameters.at(1);
    uint32_t imm = *Instruction::parameters.at(2);
    *rt = rs < imm;
}

void sltu_::execute() {
    uint32_t rs = *Instruction::parameters.at(0);
    uint32_t rt = *Instruction::parameters.at(1);
    uint32_t* rd = Instruction::parameters.at(2);
    *rd = rs < rt;
}

void sub_::execute() {
    uint32_t rs = *Instruction::parameters.at(0);
    uint32_t rt = *Instruction::parameters.at(1);
    uint32_t* rd = Instruction::parameters.at(2);

    long rsVal = (signed int)rs;
    long rtVal = (signed int)rt;
    if ((rtVal < 0) && (rsVal > INT_MAX - rtVal))
        throw GeneralExceptions::OverflowException();
    else *rd = rs - rt;
}

void subu_::execute() {
    uint32_t rs = *Instruction::parameters.at(0);
    uint32_t rt = *Instruction::parameters.at(1);
    uint32_t* rd = Instruction::parameters.at(2);
    *rd = rs - rt;
}

void j_::execute() {
    uint32_t* pc = Instruction::parameters.at(1);
    uint32_t address = *Instruction::parameters.at(0);
    *pc = address;
}

void jal_::execute() {
    uint32_t* pc = Instruction::parameters.at(2);
    uint32_t* ra = Instruction::parameters.at(0);
    uint32_t address = *Instruction::parameters.at(1);
    *ra = *pc + 8;
    *pc = address;
}

void jr_::execute() {
    uint32_t* pc = Instruction::parameters.at(1);
    uint32_t rs = *Instruction::parameters.at(0);
    *pc = rs;
}

void sll_::execute() {
    uint32_t rt = *Instruction::parameters.at(0);
    uint32_t* rd = Instruction::parameters.at(1);
    uint32_t shamt = *Instruction::parameters.at(2);
    *rd = rt << shamt;
}

void srl_::execute() {
    uint32_t rt = *Instruction::parameters.at(0);
    uint32_t* rd = Instruction::parameters.at(1);
    uint32_t shamt = *Instruction::parameters.at(2);
    *rd = rt >> shamt;
}

void beq_::execute() {
    uint32_t rt = *Instruction::parameters.at(0);
    uint32_t rs = *Instruction::parameters.at(1);
    uint32_t branchAddr = *Instruction::parameters.at(2);
    uint32_t* pc = Instruction::parameters.at(3);
    if (rs == rt){
        int16_t reativeAddr = branchAddr & 0xFFFF;
        // printf("NEW PC.at : 0x%08x : %d / RELADDR : %d / CURPC : %d\n", 0x00400000 + 4 * (*pc + re.ativeAddr), (re.ativeAddr), re.ativeAddr, *pc);
        //*pc = *pc + reativeAddr - 1;
        *pc = reativeAddr - 1;
    }
}

void bne_::execute() {
    uint32_t rt = *Instruction::parameters.at(0);
    uint32_t rs = *Instruction::parameters.at(1);
    uint32_t branchAddr = *Instruction::parameters.at(2);
    uint32_t* pc = Instruction::parameters.at(3);
    if (rs != rt){
        int16_t reativeAddr = branchAddr & 0xFFFF;
        // printf("NEW PC.at : 0x%08x : %d / RELADDR : %d / CURPC : %d\n", 0x00400000 + 4 * (*pc + re.ativeAddr), (re.ativeAddr), re.ativeAddr, *pc);
        //*pc = *pc + reativeAddr - 1;
        *pc = reativeAddr - 1;
    }
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
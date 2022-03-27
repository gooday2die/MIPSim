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

void addu_::execute() {
    uint32_t rs = *Instruction::parameters.at(0);
    uint32_t rt = *Instruction::parameters.at(1);
    uint32_t* rd = Instruction::parameters.at(2);

    *rd = rs + rt;
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
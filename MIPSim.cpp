//
// @file : MIPSim.h
// @author : Gooday2die (Isu Kim)
// @Contacts : edina00@naver.com
// @brief : 
// 

#include "MIPSim.h"

MIPSim::MIPSim(const string& argFileName) {
    this->registers = (uint32_t*) malloc(sizeof(uint32_t) * 32);
    this->pc = 0;
    this->fileName = argFileName;
    this->textSectionExpressions;
    for (uint8_t i = 0 ; i < 32 ; i++) this->registers[i] = i ;

    this->assembler = new Assembler(argFileName, &this->registers, &this->pc);
}

void MIPSim::assemble() {
    if (this->assembler) {
        this->textSectionExpressions = this->assembler->getTextSectionExpressions();
        this->textSectionExpressionCount = this->textSectionExpressions.size();

        for (uint32_t i = 0 ; i < this->textSectionExpressionCount ; i++){
            printf("[0x%08x] ", (0x00400000 + 4 * i));
            this->textSectionExpressions.at(i).print();
        }
    }
}
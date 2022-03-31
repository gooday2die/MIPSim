//
// @file : MIPSim.h
// @author : Gooday2die (Isu Kim)
// @Contacts : edina00@naver.com
// @brief : 
// 

#include "MIPSim.h"

/**
 * A constructor member function for class MIPSim
 * @param argFileName the string object that represents file name and directory
 */
MIPSim::MIPSim(const string& argFileName) {
    this->registers = (uint32_t*) malloc(sizeof(uint32_t) * 32);
    this->pc = 0;
    this->textSectionExpressions;
    for (uint8_t i = 0 ; i < 32 ; i++) this->registers[i] = i ;

    this->assembler = new Assembler(argFileName, &this->registers, &this->pc);
}

/**
 * A member function for class MIPSim that assembles all the expressions.
 * This member function prints out the result as well.
 */
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
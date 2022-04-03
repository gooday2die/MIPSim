//
// @file : Simulator.h
// @author : Gooday2die (Isu Kim)
// @Contacts : edina00@naver.com
// @brief : 
// 

#include "Simulator.h"

/**
 * A constructor member function for class Simulator
 * @param argRegisters the pointer address to array of registers
 * @param argPc the pointer address to pc
 * @param argTextSectionExpressions all text expressions.
 */
Simulator::Simulator(uint32_t** argRegisters, uint32_t* argPc, const vector<Expression>& argTextSectionExpressions) {
    this->registers = argRegisters;
    this->pc = argPc;
    this->textSectionExpressions = argTextSectionExpressions;
}

/**
 * A member function for class Simulator that runs all expressions.
 */
void Simulator::run() {
    for (Expression x : this->textSectionExpressions) {
        try {
            x.execute();
        } catch (const GeneralExceptions::OverflowException& ex){
            cout << "[EXCEPTION] Overflow exception detected" << endl;
            break;
        }
    }
}
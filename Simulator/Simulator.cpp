//
// @file : Simulator.h
// @author : Gooday2die (Isu Kim)
// @Contacts : edina00@naver.com
// @brief : A file that implements all member functions for class Simulator
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
 * A member function that prints out and executes current expression
 * @param argExpression The Expression argument to execute.
 */
void Simulator::execute(Expression argExpression) {
    printf("[0x%08x] ", (0x00400000 + 4 * *this->pc));
    argExpression.print();
    argExpression.execute();
}

/**
 * A member function for class Simulator that runs all expressions.
 */
void Simulator::run() {
    *this->pc = 0;
    while (*this->pc != this->textSectionExpressions.size()){
        try {
            this->execute(this->textSectionExpressions[*this->pc]);
            *this->pc = *this->pc + 1;
        } catch (const GeneralExceptions::OverflowException& ex){
            cout << "[EXCEPTION] Overflow exception detected" << endl;
            break;
        } catch (const Syscall::Exit& ex){
            cout << "[SYSCALL] Exit detected" << endl;
            break;
        }
    }
}
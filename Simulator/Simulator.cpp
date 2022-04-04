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
 * A member function that prints out and executes current expression
 * @param argExpression The Expression argument to execute.
 */
void Simulator::execute(Expression argExpression) {
    printf("[PC : 0x%08x] ", *this->pc);
    argExpression.print();
    argExpression.execute();
}

/**
 * A member function for class Simulator that runs all expressions.
 */
void Simulator::run() {
    for (Expression x : this->textSectionExpressions) {
        try {
            this->execute(x);
        } catch (const GeneralExceptions::OverflowException& ex){
            cout << "[EXCEPTION] Overflow exception detected" << endl;
            break;
        } catch (const Syscall::Exit& ex){
            cout << "[SYSCALL] Exit detected" << endl;
            break;
        }
    }
}
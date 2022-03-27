//
// @file : Expression.
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : 
// @date: 2022-03-27

#include "Expression.h"


Expression::Expression(Instruction* argInstruction, const string& argExpressionString, uint32_t argMachineCode) {
    this->instruction = argInstruction;
    this->expressionString = argExpressionString;
    this->machineCode = argMachineCode;
}

void Expression::execute() {
    this->instruction->execute();
}

void Expression::print(){
    cout << "Expression : " << this->expressionString;
    printf("-> Machine Code : 0x%08x \n", this->machineCode);
}
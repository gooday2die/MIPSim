//
// @file : Expression.
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : 
// @date: 2022-03-27

#include "Expression.h"

/**
 * A constructor member function for class Expression
 * @param instructionArgs the vector of arguments of registers
 * @param argExpressionString the string that represents expressions
 * @param instructionMnemonic the string that represents instruction mnemonic
 * @param argMachineCode the uint32_t type of machine Code.
 */
Expression::Expression(const vector<uint32_t*>& instructionArgs, const string& argExpressionString, const string& instructionMnemonic, uint32_t argMachineCode) {
    this->expressionString = argExpressionString;
    this->machineCode = argMachineCode;

    if (instructionMnemonic == "add"){
        this->instruction = new add_(instructionArgs);
    } else if (instructionMnemonic == "addu"){
        this->instruction = new addu_(instructionArgs);
    } else if (instructionMnemonic == "and"){
        this->instruction = new and_(instructionArgs);
    } else if (instructionMnemonic == "addi"){
        this->instruction = new addi_(instructionArgs);
    } else if (instructionMnemonic == "addiu"){
        this->instruction = new addiu_(instructionArgs);
    } else if (instructionMnemonic == "andi"){
        this->instruction = new andi_(instructionArgs);
    } else if (instructionMnemonic == "nor"){
        this->instruction = new nor_(instructionArgs);
    } else if (instructionMnemonic == "or"){
        this->instruction = new or_(instructionArgs);
    } else if (instructionMnemonic == "ori"){
        this->instruction = new ori_(instructionArgs);
    } else if (instructionMnemonic == "slt"){
        this->instruction = new slt_(instructionArgs);
    } else if (instructionMnemonic == "slti"){
        this->instruction = new slti_(instructionArgs);
    } else if (instructionMnemonic == "sltiu"){
        this->instruction = new sltiu_(instructionArgs);
    } else if (instructionMnemonic == "sltu"){
        this->instruction = new sltu_(instructionArgs);
    } else if (instructionMnemonic == "sub") {
        this->instruction = new sub_(instructionArgs);
    } else if (instructionMnemonic == "subu"){
        this->instruction = new subu_(instructionArgs);
    } else if (instructionMnemonic == "j"){
        this->instruction = new j_(instructionArgs);
    } else if (instructionMnemonic == "jal"){
        this->instruction = new jal_(instructionArgs);
    } else if (instructionMnemonic == "jr"){
        this->instruction = new jr_(instructionArgs);
    } else if (instructionMnemonic == "sll"){
        this->instruction = new sll_(instructionArgs);
    } else if (instructionMnemonic == "srl"){
        this->instruction = new srl_(instructionArgs);
    } else if (instructionMnemonic == "beq"){
        this->instruction = new beq_(instructionArgs);
    } else if (instructionMnemonic == "bne") {
        this->instruction = new bne_(instructionArgs);
    } else if (instructionMnemonic == "syscall") {
        this->instruction = new syscall_(instructionArgs);
    } else{
        this->instruction = nullptr;
    }
}

/**
 * A member function for class Expression that executes the expression
 */
void Expression::execute() {
    this->instruction->execute();
}

/**
 * A member function for class Expression that prints out the expression.
 */
void Expression::print(){
    cout << this->expressionString;
    if (this->expressionString == "syscall")  printf(" ");
    printf("(0x%08x)\n", this->machineCode);
}
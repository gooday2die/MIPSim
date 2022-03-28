//
// @file : Expression.
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : 
// @date: 2022-03-27

#include "Expression.h"


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
    } else{
        this->instruction = nullptr;
    }
}

void Expression::execute() {
    this->instruction->execute();
}

void Expression::print(){
    cout << "Expression : " << this->expressionString;
    printf("-> Machine Code : 0x%08x \n", this->machineCode);
}
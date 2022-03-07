//
// @file : RegisterHandler.cpp
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : A file that implements all member functions for class RegisterHandler
// @date: 2022-03-07

#include "RegisterHandler.h"

RegisterHandler::RegisterHandler() {
    this->registers = (Register*)malloc(sizeof(Register) * 32);
    this->pc = Register(0);

    for(uint8_t i = 0 ; i < 32 ; i++) this->registers[i] = 0;
}

Register* RegisterHandler::getRegister(int registerIndex) {
    return this->registers + registerIndex;
}

Register RegisterHandler::getPC(){
    return this->pc;
}

Register* RegisterHandler::getAllRegisters() {
    return this->registers;
}

void RegisterHandler::printAllRegisters() {
    printf("Registers:\n");
    for(uint8_t i = 0 ; i < 32 ; i++){
        printf("$%2d : hex : 0x%08x / signed int : %d\n", i, this->registers[i].getValue(), this->registers[i].getValue());
    }
}
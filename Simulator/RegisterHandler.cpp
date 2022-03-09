//
// @file : RegisterHandler.cpp
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : A file that implements all member functions for class RegisterHandler
// @date: 2022-03-07

#include "RegisterHandler.h"

RegisterHandler::RegisterHandler() {
    this->registers = (uint32_t *)malloc(sizeof(uint32_t) * 32);
    this->pc = 0;
    for(uint8_t i = 0 ; i < 32 ; i++) this->registers[i] = 0;
}

uint32_t* RegisterHandler::getRegister(int registerIndex) {
    return this->registers + registerIndex;
}

uint32_t* RegisterHandler::getPC(){
    return &this->pc;
}

uint32_t* RegisterHandler::getAllRegisters() {
    return this->registers;
}

void RegisterHandler::printAllRegisters() {
    printf("Registers:\n");
    for(uint8_t i = 0 ; i < 32 ; i++){
        printf("$%2d : hex : 0x%08x / signed int : %d\n", i, this->registers[i], this->registers[i]);
    }
}
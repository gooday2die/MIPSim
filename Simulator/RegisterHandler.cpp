//
// @file : RegisterHandler.cpp
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : A file that implements all member functions for class RegisterHandler
// @date: 2022-03-07

#include "RegisterHandler.h"

/**
 * A constructor member function for RegisterHandler class
 * This sets all 32 registers + PC
 */
RegisterHandler::RegisterHandler() {
    this->registers = (uint32_t *)malloc(sizeof(uint32_t) * 32);
    this->pc = 0;
    for(uint8_t i = 0 ; i < 32 ; i++) this->registers[i] = 0;
}

/**
 * A member function for class RegisterHandler for retrieving a register
 * @param registerIndex the register index to look for
 * @return returns register's pointer
 */
uint32_t* RegisterHandler::getRegister(int registerIndex) {
    return this->registers + registerIndex;
}

/**
 * A member function for getting PC
 * @return returns PC register's pointer
 */
uint32_t* RegisterHandler::getPC(){
    return &this->pc;
}

/**
 * A member function that gets all registers
 * @return returns an array of registers
 */
uint32_t* RegisterHandler::getAllRegisters() {
    return this->registers;
}

/**
 * A member function for printing out all registers
 */
void RegisterHandler::printAllRegisters() {
    printf("Registers:\n");
    for(uint8_t i = 0 ; i < 32 ; i++){
        printf("$%2d : hex : 0x%08x / signed int : %d\n", i, this->registers[i], this->registers[i]);
    }
}
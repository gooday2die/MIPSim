//
// @file : SimulatorTests.cpp
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : A file that implements all member functions for class SimulatorTests
// @date: 2022-03-07

#include "SimulatorTests.h"

SimulatorTests::SimulatorTests() {
    ;
}

/**
 * A member function for class SimulatorTests for testing addi and add instruction
 */
void SimulatorTests::test_add_addi() {
    this->s.printAllRegisters();

    uint32_t a = 0b00100000000000000000000000001010;
    // addi $0 $0 10 (I know this is dumb since $0 is hardwired, just for testing)
    uint32_t b = 0b00100000001000010000000000001111;
    // addi $1 $1 15
    uint32_t c = 0b00000000000000010001000000100000;
    // add $0 $1 $2

    this->s.executeMachineCode(a);
    this->s.executeMachineCode(b);
    this->s.executeMachineCode(c);

    this->s.printAllRegisters();

    *(this->s.getRegister(3)) = 0x7FFFFFFF;
    this->s.printAllRegisters();

    // set $3 0xFFFFFFFF
    uint32_t d = 0b00000000011000010010000000100000;
    // add $3 $1 $4 > shall overflow and throw overflow exception
    try {
        this->s.executeMachineCode(d);
    } catch (std::overflow_error){
        std::cout << "OVERFLOWED" << std::endl;
    }
    this->s.printAllRegisters();

    uint32_t e = 0b00100000011000110000000000001111;
    // addi $3 $3 15 > shall overflow and throw exception.
    try {
        this->s.executeMachineCode(e);
    } catch (std::overflow_error){
        std::cout << "OVERFLOWED" << std::endl;
    }
    this->s.printAllRegisters();
}


/**
 * A member function for class SimulatorTests for testing addiu and addu instruction
 */
void SimulatorTests::test_addu_addiu() {
    this->s.printAllRegisters();

    uint32_t a = 0b00100100000000000000000000001010;
    // addiu $0 $0 10 (I know this is dumb since $0 is hardwired, just for testing)
    uint32_t b = 0b00100100001000010000000000001111;
    // addiu $1 $1 15
    uint32_t c = 0b00000000000000010001000000100001;
    // addu $0 $1 $2

    this->s.executeMachineCode(a);
    this->s.executeMachineCode(b);
    this->s.executeMachineCode(c);

    this->s.printAllRegisters();

    *(this->s.getRegister(3)) = 0x7FFFFFFF;
    this->s.printAllRegisters();

    // set $3 0xFFFFFFFF
    uint32_t d = 0b00000000011000010010000000100001;
    // addu $3 $1 $4 > shall overflow but throw no exceptions
    try {
        this->s.executeMachineCode(d);
    } catch (std::overflow_error){
        std::cout << "OVERFLOWED" << std::endl;
    }
    this->s.printAllRegisters();

    uint32_t e = 0b00100100011000110000000000001111;
    // addiu $3 $3 15 > shall overflow but throw no exceptions
    try {
        this->s.executeMachineCode(e);
    } catch (std::overflow_error){
        std::cout << "OVERFLOWED" << std::endl;
    }
    this->s.printAllRegisters();
}


/**
 * A member function for class SimulatorTests for testing and and andi instruction
 */
void SimulatorTests::test_and_andi() {
    this->s.printAllRegisters();
    *(this->s.getRegister(0)) = 0x000000FF;
    *(this->s.getRegister(1)) = 0x00000011;


    uint32_t a = 0b00000000000000010001000000100100;
    // and $0 $1 $2

    this->s.executeMachineCode(a);
    this->s.printAllRegisters();

    uint32_t b = 0b00110000000000010000000000000011;
    // andi $0 $1 3
    this->s.executeMachineCode(b);
    this->s.printAllRegisters();

}

/**
 * A member function for class SimulatorTests for testing or and nor instruction
 */
void SimulatorTests::test_or_nor() {
    this->s.printAllRegisters();
    *(this->s.getRegister(0)) = 0x000000FF;
    *(this->s.getRegister(1)) = 0x00000011;


    uint32_t a = 0b00000000000000010001000000100111;
    // nor $0 $1 $2

    this->s.executeMachineCode(a);
    this->s.printAllRegisters();

    this->s.printAllRegisters();
    *(this->s.getRegister(0)) = 0x000000FF;
    *(this->s.getRegister(1)) = 0x00000011;

    uint32_t b = 0b00000000000000010001000000100101;
    // 0or $0 $1 $2

    this->s.executeMachineCode(b);
    this->s.printAllRegisters();
}
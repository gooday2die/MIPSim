//
// @file : SimulatorTests.cpp
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : A file that implements all member functions for class SimulatorTests
// @date: 2022-03-07

#include "SimulatorTests.h"

/**
 * A member function for class SimulatorTests for testing addi, add, sub, srl, sll
 */
void SimulatorTests::test1(){
    Translator a = Translator();
    uint32_t r1 = a.generateMachineCode("addi $1, $1, 10 ");
    uint32_t r2 = a.generateMachineCode("addi $2, $2, 15 ");
    uint32_t r3 = a.generateMachineCode("add $1, $2, $3 ");
    uint32_t r4 = a.generateMachineCode("sub $3 $2 $4 ");
    uint32_t r5 = a.generateMachineCode("sll $4 $4 2 ");
    uint32_t r6 = a.generateMachineCode("srl $4 $5 1 ");

    uint32_t branches[1] = {0xFFFFFFFF};
    uint32_t codes[7] = {r1,r2,r3, r4, r5, r6,0xF0F0F0F0};

    Simulator s = Simulator(branches, codes);
    s.printAllRegisters();
    s.run();
    s.printAllRegisters();
}
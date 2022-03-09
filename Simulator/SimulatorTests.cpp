//
// @file : SimulatorTests.cpp
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : A file that implements all member functions for class SimulatorTests
// @date: 2022-03-07

#include "SimulatorTests.h"

/**
 * A member function for class SimulatorTests for testing addi and add instruction
 */
void SimulatorTests::test_add_addi() {
    uint32_t branches[1] = {0xFFFFFFFF};
    uint32_t codes[5] = {0x2021000a,0x2042000f,0x00221820, 0x00622022, 0xF0F0F0F0};


    Simulator s = Simulator(branches, codes);
    s.printAllRegisters();

    s.run();
    s.printAllRegisters();
}

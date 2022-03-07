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
    this->s.registerHandler.printAllRegisters();

    MachineCode a = MachineCode(0b00100000000000000000000000001010, 2);
    // addi $0 $0 10 (I know this is dumb since $0 is hardwired, just for testing)
    MachineCode b = MachineCode(0b00100000001000010000000000001111, 2);
    // addi $1 $1 15
    MachineCode c = MachineCode(0b00000000000000010001000000100000, 1);
    // add $0 $1 $2

    this->s.machineCodeSimulator.executeCode(a);
    this->s.machineCodeSimulator.executeCode(b);
    this->s.machineCodeSimulator.executeCode(c);

    this->s.registerHandler.printAllRegisters();

    this->s.registerHandler.getRegister(3)->setValue(0xFFFFFFFF);
    this->s.registerHandler.printAllRegisters();

    // set $3 0xFFFFFFFF
    MachineCode d = MachineCode(0b00000000011000010010000000100000, 1);
    // add $3 $1 $4 > shall overflow and throw overflow exception
    this->s.machineCodeSimulator.executeCode(d);


}
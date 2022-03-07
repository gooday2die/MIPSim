//
// @file : Simulator.cpp
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : A file that implements all member functions for class Simulator
// @date: 2022-03-07

#include "Simulator.h"

void Simulator::tester() {
    this->registerHandler.printAllRegisters();
    MachineCode a = MachineCode(0b00100000000000000000000000001010, 2);
    MachineCode b = MachineCode(0b00100000001000010000000000001111, 2);
    MachineCode c = MachineCode(0b00000000000000010001000000100000, 1);

    this->machineCodeSimulator.executeCode(a);

    this->machineCodeSimulator.executeCode(b);

    this->machineCodeSimulator.executeCode(c);

    this->registerHandler.printAllRegisters();
}

Simulator::Simulator() {
    std::cout << "===== MIPSim Version : " << MIPSIM_VERSION << " by Gooday2die =====" << std::endl;
    this->tester();
}
//
// @file : Simulator.cpp
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : A file that implements all member functions for class Simulator
// @date: 2022-03-07

#include "Simulator.h"


/**
 * A constructor member function for class Simulator
 */
Simulator::Simulator(uint32_t *argBranches){
    this->branches = argBranches;
    this->machineCodeSimulator.setBranches(this->branches);
    std::cout << "===== MIPSim Version : " << MIPSIM_VERSION << " by Gooday2die =====" << std::endl;
}

/**
 * A member function that gets specific Register's pointer by index
 * @param index the index of the register
 * @return returns Register's pointer
 */
uint32_t* Simulator::getRegister(int index) {
    return this->registerHandler.getRegister(index);
}

/**
 * A member function that executes specific MachineCode
 * @param machineCode the machineCode object to execute
 */
void Simulator::executeMachineCode(uint32_t machineCode) {
    this->machineCodeSimulator.executeCode(machineCode);
}

/**
 * A member function that prints out all registers
 */
void Simulator::printAllRegisters() {
    this->registerHandler.printAllRegisters();
}
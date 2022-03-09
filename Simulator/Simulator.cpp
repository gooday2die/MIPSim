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
Simulator::Simulator(uint32_t *argBranches, uint32_t* argMemory){
    this->branches = argBranches;
    this->machineCodeSimulator.setBranches(this->branches);
    this->memory = argMemory;
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

/**
 * A member function that runs the codes in the memory.
 */
void Simulator::run() {
    clock_t begin = clock();
    printf("Starting Job...\n");

    while (true){
        uint32_t curMachineCode = this->memory[*this->registerHandler.getPC()];
        if (curMachineCode == 0xF0F0F0F0) break;
        printf("CURPC : 0x%08x / MACHINECODE : 0x%08x\n", *this->registerHandler.getPC(), curMachineCode);
        try {
            this->executeMachineCode(curMachineCode);
        } catch(std::exception e) {
            std::cout << "Exception : " << e.what() << std::endl;
        }
        *this->registerHandler.getPC() = *this->registerHandler.getPC() + 1;
    }
    clock_t end = clock();

    printf("Finished in %f \n", (double)(end - begin) / CLOCKS_PER_SEC);
}
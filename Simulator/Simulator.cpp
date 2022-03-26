//
// @file : Simulator.cpp
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : A file that implements all member functions for class Simulator
//

#include "Simulator.h"


/**
 * A constructor member function for class Simulator
 */
Simulator::Simulator(map<string, uint32_t*> machineCodes){
    cout << "===== MIPSim Version : " << MIPSIM_VERSION << " by Gooday2die =====" << endl;
    try{
        this->textSection = machineCodes.at("text");
    } catch (const out_of_range& ex){
        cout << "Cannot find text section from code" << endl;
        cout << "Nothing to execute" << endl;
    }
}

/**
 * A member function that gets specific Register's pointer by index
 * @param index the index of the register
 * @return returns Register's pointer
 */
uint32_t* Simulator::getRegister(int index) {
    return this->registerHandler->getRegister(index);
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
    this->registerHandler->printAllRegisters();
}

/**
 * A member function that runs the codes in the memory.
 */
void Simulator::run() {
    clock_t begin = clock();
    printf("Starting Job...\n");

    while (true){
        uint32_t curMachineCode = this->textSection[*this->registerHandler->getPC()];
        if (this->textSection[*this->registerHandler->getPC()] == 0xF0F0F0F0) break;
        printf("Current Address : 0x%08x / MACHINECODE : 0x%08x\n", (0x00400000 + 4 * (*this->registerHandler->getPC())), curMachineCode);
        try {
            this->executeMachineCode(curMachineCode);
        } catch (const Syscall::Exit& ex){ // when syscall, break
            cout << "[SYSCALL] Exit" << endl;
            break;
        } catch (const GeneralExceptions::OverflowException& ex){
            cout << "[EXCEPTION] Overflow exception detected" << endl;
            break;
        } catch (const GeneralExceptions::UnknownInstruction& ex){
            cout << "[EXCEPTION] Unknown instruction found" << endl;
            break;
        }
        this->registerHandler->resetZero();
        *this->registerHandler->getPC() = *this->registerHandler->getPC() + 1;
    }
    clock_t end = clock();

    printf("Finished in %f \n", (double)(end - begin) / CLOCKS_PER_SEC);
}
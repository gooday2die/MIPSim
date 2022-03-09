#include "Simulator/SimulatorTests.h"
#include "Parser/Assembler.h"
#include "Simulator/Simulator.h"


int main() {
    Assembler a = Assembler();
    uint32_t r1 = a.generateMachineCode("addi $1, $1, 10 ");
    printf("Code : 0x%08x\n", r1);
    uint32_t r2 = a.generateMachineCode("addi $2, $2, 15 ");
    printf("Code : 0x%08x\n", r2);
    uint32_t r3 = a.generateMachineCode("add $1, $2, $3 ");
    printf("Code : 0x%08x\n", r3);
    uint32_t r4 = a.generateMachineCode("sub $3 $2 $4 ");
    printf("Code : 0x%08x\n", r4);

    uint32_t branches[1] = {0xFFFFFFFF};
    uint32_t codes[5] = {r1,r2,r3, r4, 0xF0F0F0F0};

    Simulator s = Simulator(branches, codes);
    s.printAllRegisters();
    s.run();
    s.printAllRegisters();
    //SimulatorTests st = SimulatorTests();
    //st.test_add_addi();
    //st.test_addu_addiu();
    //st.test_or_nor();
}

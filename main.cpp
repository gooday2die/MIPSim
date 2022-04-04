#include "Utils/Expression.h"
#include "Utils/Instruction.h"
#include "MIPSim.h"


#include <vector>
using namespace std;
int main() {
    MIPSim mipSim = MIPSim("test.txt");
    mipSim.assemble();
    mipSim.printRegisters();
    mipSim.simulate();
    mipSim.printRegisters();
    /**
    uint32_t* registers;
    uint32_t pc;

    registers = (uint32_t*) malloc(sizeof(uint32_t) * 32);
    for (uint8_t i = 0 ; i < 32 ; i++) registers[i] = 0;
    std::vector<uint32_t*> instargs;
    instargs.emplace_back(registers + 0);
    instargs.emplace_back(registers + 2);
    uint32_t imm = 100;

    instargs.emplace_back(&imm);
    for (uint8_t i = 0 ; i < 32 ; i++) printf("%d\n", registers[i]);

    Expression exp = Expression(instargs, "ori $0 $v0 100", "ori", 0x00);
    exp.execute();
    printf("\n");
    for (uint8_t i = 0 ; i < 32 ; i++) printf("%d\n", registers[i]);
    **/
}

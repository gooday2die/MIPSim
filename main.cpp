#include "Utils/Expression.h"
#include "Utils/Instruction.h"
#include "MIPSim.h"

using namespace std;
int main() {
    MIPSim mipSim = MIPSim("test.txt");
    mipSim.assemble();
    mipSim.printRegisters();
}

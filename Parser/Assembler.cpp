//
// @file : Assembler.cpp
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : A file that implements all member functions for class Assembler
// @date: 2022-03-10

#include "Assembler.h"

/**
 * A constructor member function for class Assembler.
 * This does the following things.
 * 1. Read file
 * 2. Preprocess the expressions and instructions
 * 3. Manage branches and all necessary things
 * 4. Translate into Machine code
 * 5. Execute machine code using Simulator
 * @param fileName
 */
Assembler::Assembler(const char* fileName) {
    std::cout << "===== MIPSim Assembler Version : " << MIPSIM_VERSION << " by Gooday2die =====" << std::endl;
    FileReader fileReader = FileReader(fileName); // Read file
    this->allExpressions = fileReader.getAllExpressions(); // get all expressions
    this->allBranches = fileReader.getAllBranches(); // get all branches
    this->allMachineCodes = (uint32_t *) malloc(sizeof(uint32_t) * (this->allExpressions.size() + 1));
    // we also need 0xF0F0F0F0, so we need size + 1
    this->allMachineCodes[this->allExpressions.size()] = 0xF0F0F0F0; // let our program know it was last instruction
    uint32_t* branches = (uint32_t*) malloc(sizeof(uint32_t) * (this->allBranches.size() + 1));
    // all branches in one uint32_t array. Also, 0xFFFFFFFF denotes the last of the branch, so we need size + 1

    translateAll(); // translate all assembly code into machine code instructions.

    //for(uint32_t i = 0 ; i < this->allExpressions.size() ; i++) // Just print all Instructions and all machine codes
    //    printf("CurCode Instruction# %d: 0x%08x\n", i, this->allMachineCodes[i]);

    uint32_t branchCount = 0; // dump all branches
    for (auto const& y : this->allBranches){  // get all branches
        branches[branchCount] = y.second;
        branchCount++;
    }

    std::cout << "Assembler Successfully Finished!" << std::endl;
    std::cout << "- Generated Expressions : " << this->allExpressions.size() << std::endl;
    std::cout << "- Generated Branches : " << this->allBranches.size() << std::endl;


    Simulator simulator = Simulator(this->allMachineCodes); // intialize
    simulator.printAllRegisters(); // print registers
    simulator.run(); // then run
    simulator.printAllRegisters(); // print registers
}

/**
 * A member function that replaces branch string into the instruction address
 * @param curExpression the string object of expression to change branch into instruction address
 * @return returns string object that contains the instruction instead of branch string
 */
std::string Assembler::replaceBranches(std::string curExpression) {
    for (auto const& y : this->allBranches){  // get all branches
        std::string branchString = y.first;
        replaceString(curExpression, branchString, std::to_string(y.second - 1));
    }
    return curExpression;
}

/**
 * A member function that replaces substring to another in a string
 * @param str the original string
 * @param from the string to be changed
 * @param to the string to change into
 * @return returns true if there were any changes, false if not
 */
bool Assembler::replaceString(std::string& str, const std::string& from, const std::string& to) {
    size_t start_pos = str.find(from);
    if(start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}

/**
 * A member function that translates a single line into a machine code
 * @param curLine the current line to translate into
 * @return returns uint32_t type machine code that was translated from original
 */
uint32_t Assembler::translateLine(std::string curLine) {
    std::string curTranslated = replaceBranches(curLine);
    uint32_t result = Translator::generateMachineCode(curTranslated.c_str());
    return result;
}

/**
 * A member function that translates all expressions into machine code.
 * This saves all machine codes into the allMachineCodes variable.
 */
void Assembler::translateAll(){
    uint32_t curIndex = 0;
    for (auto const& y : this->allExpressions){  // get all expressions
        std::string curExpression = y.second;
        curExpression = replaceBranches(curExpression);
        uint32_t curMachineCode = translateLine(curExpression);
        this->allMachineCodes[curIndex] = curMachineCode;
        curIndex++;
    }
}
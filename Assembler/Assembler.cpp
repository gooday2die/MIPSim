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
    this->setRegisterNames();
    this->allExpressions = fileReader.getAllExpressions(); // get all expressions

    this->assemble();

    //for(uint32_t i = 0 ; i < this->allExpressions.size() ; i++) // Just print all Instructions and all machine codes
    //    printf("CurCode Instruction# %d: 0x%08x\n", i, this->allMachineCodes[i]);

    std::cout << "Assembler Successfully Finished!" << std::endl;
    std::cout << "- Generated Expressions : " << this->allExpressions.size() << std::endl;
    std::cout << "- Generated Branches : " << this->allBranches.size() << "\n" << std::endl;

    Simulator simulator = Simulator(this->allMachineCodes); // intialize
    simulator.printAllRegisters(); // print registers
    simulator.run(); // then run
    simulator.printAllRegisters(); // print registers
}

/**
 * A member function for class Assembler that assembles the whole code into machine code
 */
void Assembler::assemble(){
    this->checkGrammar();

    std::cout << "\nResult : " << std::endl;
    if(this->totalErrorCount > 0){
        std::cout << ASSEMBLE_FAILED << std::endl;
        std::cout << "Found " << this->totalErrorCount << " error(s)" << std::endl;
        exit(1);
    }else{
        this->allMachineCodes = (uint32_t *) malloc(sizeof(uint32_t) * (this->processedExpressions.size() + 1));
        this->allMachineCodes[this->processedExpressions.size()] = 0xF0F0F0F0; // let our program know it was last instruction
        this->translateAll();
        std::cout << ASSEMBLE_SUCCESS << std::endl;
    }
}

/**
 * A member function for class Assembler that checks grammar for the entire code.
 * This also adds all the branches into the allBranches attribute.
 */
void Assembler::checkGrammar() {
    uint32_t expressionCount = 0; // total expression count for branches
    this->totalLineCount = 0; // total line count

    for (auto const& x : this->allExpressions){ // for all expressions
        std::string curLine = x.second;
        if(!curLine.empty()){ // if current line was empty line, skip
            Expression curExpression = Expression(curLine);
            if(curExpression.isBranchExpression()){ // if current line is a branch expression
                std::string branchName = curExpression.getBranchName();
                try{
                    GrammarChecker::checkBranchName(branchName, this->allBranches);
                    this->allBranches.insert(std::pair<std::string, int>(branchName, expressionCount));
                } catch(BranchExceptions::duplicateNameException const& ex){
                    std::cout << ERROR_TAG << " Branch with duplicate name was found ";
                    std::cout << "@ln " << this->totalLineCount << " -> " << ERROR_EXPRESSION << std::endl;
                    this->totalErrorCount++;
                } catch(BranchExceptions::emptyNameException const& ex){
                    std::cout << ERROR_TAG << " Branch name cannot be empty string ";
                    std::cout << "@ln " << this->totalLineCount << " -> " << ERROR_EXPRESSION << std::endl;
                    this->totalErrorCount++;
                } catch(BranchExceptions::whitespaceNameException const& ex){
                    std::cout << ERROR_TAG << " Branch name cannot contain whitespace ";
                    std::cout << "@ln " << this->totalLineCount << " -> " << ERROR_EXPRESSION << std::endl;
                    this->totalErrorCount++;
                }
            } else{
                curExpression.preprocess();

                std::string expressionString = curExpression.getString();
                expressionString = replaceRegisterName(expressionString);
                expressionString = replaceBranches(expressionString);
                try {
                    expressionString = replaceBranches(expressionString);
                    GrammarChecker::checkExpressionValidity(expressionString, this->allBranches);
                    this->processedExpressions.insert(std::pair<uint32_t, std::string>(expressionCount, expressionString));
                } catch(ExpressionExceptions::unknownRegisterException const& ex){
                    std::cout << ERROR_TAG << " Unknown register ";
                    std::cout << "@ln " << this->totalLineCount << " -> " << ERROR_EXPRESSION << std::endl;
                    this->totalErrorCount++;
                } catch(ExpressionExceptions::invalidArgumentException const& ex){
                    std::cout << ERROR_TAG << " Invalid arguments for instruction ";
                    std::cout << "@ln " << this->totalLineCount << " -> " << ERROR_EXPRESSION << std::endl;
                    this->totalErrorCount++;
                } catch(ExpressionExceptions::unknownInstructionMnemonicException const& ex){
                    std::cout << ERROR_TAG << " Unknown Instruction mnemonic ";
                    std::cout << "@ln " << this->totalLineCount << " -> " << ERROR_EXPRESSION << std::endl;
                    this->totalErrorCount++;
                }
                expressionCount++;
            }
        }
        this->totalLineCount++;
    }
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
    for (auto const& y : this->processedExpressions){  // get all expressions
        std::string curLine = y.second;
        if (!curLine.empty() && !(Expression(y.second).isBranchExpression())) {
            curLine = replaceBranches(curLine);
            uint32_t curMachineCode = 0x00000000;
            curMachineCode = translateLine(curLine);
            this->allMachineCodes[curIndex] = curMachineCode;
            curIndex++;
        }
    }
}

/**
 * A member function for FileReader that sets the map of all register name's alias into register's index
 */
void Assembler::setRegisterNames(){
    this->registerNames.insert(std::pair<std::string, uint8_t>("zero",0));
    this->registerNames.insert(std::pair<std::string, uint8_t>("at", 1));
    this->registerNames.insert(std::pair<std::string, uint8_t>("v0", 2));
    this->registerNames.insert(std::pair<std::string, uint8_t>("v1", 3));
    this->registerNames.insert(std::pair<std::string, uint8_t>("a0", 4));
    this->registerNames.insert(std::pair<std::string, uint8_t>("a1", 5));
    this->registerNames.insert(std::pair<std::string, uint8_t>("a2", 6));
    this->registerNames.insert(std::pair<std::string, uint8_t>("a3", 7));
    this->registerNames.insert(std::pair<std::string, uint8_t>("t0", 8));
    this->registerNames.insert(std::pair<std::string, uint8_t>("t1", 9));
    this->registerNames.insert(std::pair<std::string, uint8_t>("t2", 10));
    this->registerNames.insert(std::pair<std::string, uint8_t>("t3", 11));
    this->registerNames.insert(std::pair<std::string, uint8_t>("t4", 12));
    this->registerNames.insert(std::pair<std::string, uint8_t>("t5", 13));
    this->registerNames.insert(std::pair<std::string, uint8_t>("t6", 14));
    this->registerNames.insert(std::pair<std::string, uint8_t>("t7", 15));
    this->registerNames.insert(std::pair<std::string, uint8_t>("s0", 16));
    this->registerNames.insert(std::pair<std::string, uint8_t>("s1", 17));
    this->registerNames.insert(std::pair<std::string, uint8_t>("s2", 18));
    this->registerNames.insert(std::pair<std::string, uint8_t>("s3", 19));
    this->registerNames.insert(std::pair<std::string, uint8_t>("s4", 20));
    this->registerNames.insert(std::pair<std::string, uint8_t>("s5", 21));
    this->registerNames.insert(std::pair<std::string, uint8_t>("s6", 22));
    this->registerNames.insert(std::pair<std::string, uint8_t>("s7", 23));
    this->registerNames.insert(std::pair<std::string, uint8_t>("t8", 24));
    this->registerNames.insert(std::pair<std::string, uint8_t>("t9", 25));
    this->registerNames.insert(std::pair<std::string, uint8_t>("k0", 26));
    this->registerNames.insert(std::pair<std::string, uint8_t>("k1", 27));
    this->registerNames.insert(std::pair<std::string, uint8_t>("gp", 28));
    this->registerNames.insert(std::pair<std::string, uint8_t>("sp", 29));
    this->registerNames.insert(std::pair<std::string, uint8_t>("fp", 30));
    this->registerNames.insert(std::pair<std::string, uint8_t>("ra", 31));
}

/**
 * A member function that replaces register's name into register's index
 * @param curLine current line to look for
 * @return returns string object that contains register's name replaced into index
 */
std::string Assembler::replaceRegisterName(const std::string& curLine) {
    std::string resultString = curLine;
    for (auto const& x : this->registerNames){
        resultString = std::regex_replace(resultString, std::regex(x.first), std::to_string(x.second));
    }
    return resultString;
}
//
// @file : GrammarChecker.cpp
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : A file that implements all member functions for class GrammarChecker
// @date: 2022-03-12

#include "GrammarChecker.h"

#include <utility>

/**
 * A member function for class GrammarChecker that checks branch name is valid
 * @param curLine the string object to find out if the branch name is valid
 * @param allBranchNames all branch's names
 */
void GrammarChecker::checkBranchName(const std::string& curLine, std::map<std::string, uint32_t> allBranchNames) {
    if(isDuplicateBranchName(curLine, std::move(allBranchNames))) { // check if same duplicate branch exists
        throw BranchExceptions::duplicateNameException();
    } else if(curLine.find(32) != std::string::npos){ // check if branch as any whitespaces
        throw BranchExceptions::whitespaceNameException();
    } else if(curLine.empty()){ // check if the branch name was empty
        throw BranchExceptions::emptyNameException();
    }
}

/**
 * A member function for GrammarChecker that retrieves if a branch's name is duplicate or not
 * @param branchName the string object that represents branch's name
 * @return true if it is a duplicate named branch, false if not
 */
bool GrammarChecker::isDuplicateBranchName(const std::string& branchName, const std::map<std::string, uint32_t>& allBranchNames) {
    bool result = std::any_of(allBranchNames.begin(), allBranchNames.end(), [&branchName](auto const& x){
        if (x.first == branchName) return true;
    });
    return result;
}

/**
 * A member function for GrammarChecker that checks if an expression is valid in syntax
 * @param currentExpression the string object that represent current expression
 * @param allBranchNames all branches
 */
void GrammarChecker::checkExpressionValidity(std::string currentExpression, std::map<std::string, uint32_t> allBranchNames) {
    checkArgumentsValidity(currentExpression);
}

/**
 * A member function for GrammarChecker that gets an instruction type from the instruction string
 * @param instructionString the mnemonic string to check type for
 * @return returns 1 if R type, 2 if I type, 3 if J type
 */
uint8_t GrammarChecker::getInstructionType(const std::string& instructionString) {
    if ((instructionString == "add") // R Type instructions
        || (instructionString == "addu")
        || (instructionString == "and")
        || (instructionString == "nor")
        || (instructionString == "or")
        || (instructionString == "slt")
        || (instructionString == "sltu")
        || (instructionString == "sub")
        || (instructionString == "subu")
        || (instructionString == "jr")) return 1;

    else if ((instructionString == "addi") // I Type instructions
            || (instructionString == "addiu")
            || (instructionString == "andi")
            || (instructionString == "ori")
            || (instructionString == "slti")
            || (instructionString == "sltiu")
            || (instructionString == "beq")
            || (instructionString == "bne")
            || (instructionString == "sll")
            || (instructionString == "srl")) return 2;

    else if ((instructionString == "j") || instructionString == "jal") return 3; // J Type instructions
    else if ((instructionString == "move") // pseudo instructions
            || (instructionString == "li")
            || (instructionString == "lw")
            || (instructionString == "la")
            || (instructionString == "move")
            || (instructionString == "blt")
            || (instructionString == "ble")
            || (instructionString == "bgt")
            || (instructionString == "bge")) return 4;
    else throw ExpressionExceptions::unknownInstructionMnemonicException(); // unknown instruction
}

/**
 * A member function for class GrammarChecker that checks arguments validity.
 * This checks if R type has 3 parameters of registers, I type has 2 parameters of registers, J type if it has 1 address
 * @param currentExpression
 */
void GrammarChecker::checkArgumentsValidity(const std::string &currentExpression) {
    std::string space_delimiter = " ";
    std::vector<std::string> words{};
    std::string copiedExpression = currentExpression;

    size_t pos = 0;
    /**
     * A bit of bug here. If the expression string does not have whitespace in the end of expression, it does not
     * recognize 3rd parameter as its value. Thus put a whitespace in every expressions.
     */
    while ((pos = copiedExpression.find(space_delimiter)) != std::string::npos) { // split expression with whitespace
        words.push_back(copiedExpression.substr(0, pos));
        copiedExpression.erase(0, pos + space_delimiter.length());
    }

    std::string instructionMnemonic = words[0]; // split words
    /**
    uint8_t instructionType = getInstructionType(instructionMnemonic);
    uint8_t registerCount = std::count(currentExpression.begin(), currentExpression.end(), '$'); // count how many $ exists.
    uint8_t wordSizeForTypes = 0 ; // the last index of the register from words object

    switch (instructionType) {
        case 1:{ // if R type, it should have 3 registers and total of 4 parts
            if ((registerCount != 3) || (words.size() != 4)) throw ExpressionExceptions::invalidArgumentException();
            wordSizeForTypes = 4;
            break;
        }
        case 2: // if I type, it should have 2 registers and total of 4 parts
            if ((registerCount != 2) || (words.size() != 4)) throw ExpressionExceptions::invalidArgumentException();
            wordSizeForTypes = 3;
            break;
        case 3: // if J type, it should have 0 registers and 1 address. Total of 2 parts.
            if ((registerCount != 0) || (words.size() != 2)) throw ExpressionExceptions::invalidArgumentException();
            wordSizeForTypes = 2;
            break;
        default: // will not be reachable
            throw ExpressionExceptions::unknownInstructionMnemonicException();
    }
     */
    argumentInfo instructionInfo = getArgumentInfo(words[0]);
    argumentInfo expressionArguments = getExpressionArguments(currentExpression);
    //std::cout << currentExpression << std::endl;
    //printf("CurLine %d %d %d %d\n", expressionArguments.total, expressionArguments.registers, expressionArguments.addresses, expressionArguments.immediates);
    //printf("Should be %d %d %d %d\n", instructionInfo.total, instructionInfo.registers, instructionInfo.addresses, instructionInfo.immediates);

    if (instructionInfo.total == 0) throw ExpressionExceptions::unknownInstructionMnemonicException();
    else{
        uint8_t totalArgProcessed = 0;
        // check instruction's arguments were correct
        if ((instructionInfo.total == expressionArguments.total) && // check if total arguments were the correct
        (instructionInfo.addresses == expressionArguments.addresses) && // check if total addresses were correct
        (instructionInfo.registers == expressionArguments.registers) && // check if registers were correct
        (instructionInfo.immediates == expressionArguments.immediates)){ // check if immediates were correct
            for(uint8_t i = 1 ; i < 1 + instructionInfo.registers ; i++) { // check register's validity
                std::string curArgument = words[i];
                if (std::count(curArgument.begin(), curArgument.end(), '$') != 1) // if this was not a register
                    throw ExpressionExceptions::invalidArgumentException(); // throw exception
                else{ // if this was a register
                    try{ // try checking if the register was correct
                        curArgument.erase(std::remove(curArgument.begin(), curArgument.end(), '$'), curArgument.end());
                        curArgument.erase(std::remove(curArgument.begin(), curArgument.end(), ','), curArgument.end());
                        uint32_t translatedInt = std::stoi(curArgument);
                        if ((translatedInt > 31) || (translatedInt < 0)) throw ExpressionExceptions::unknownRegisterException();
                    }
                    catch (std::invalid_argument const& ex){ // if it cannot be processed using stoi, it is unknown register
                            throw ExpressionExceptions::unknownRegisterException();
                    }
                }
                totalArgProcessed++;
            }
            try{
                if (totalArgProcessed == instructionInfo.total) return;
                std::string curArgument = words[instructionInfo.registers + 1];
                curArgument.erase(std::remove(curArgument.begin(), curArgument.end(), '&'), curArgument.end());
                uint32_t translatedInt = std::stoi(curArgument);
            }
            catch (std::invalid_argument const& ex){ // if it cannot be processed using stoi, it is unknown register
                throw ExpressionExceptions::invalidArgumentException();
            }
        } else throw ExpressionExceptions::invalidArgumentException();
    }
}

argumentInfo GrammarChecker::getArgumentInfo(const std::string& instruction){
    argumentInfo result;
    uint8_t arguments;
    if (instruction == "add") arguments = InstructionArgInfo::Aadd;
    else if (instruction == "and") arguments = InstructionArgInfo::Aand;
    else if (instruction == "nor") arguments = InstructionArgInfo::Anor;
    else if (instruction == "or") arguments = InstructionArgInfo::Aor;
    else if (instruction == "slt") arguments = InstructionArgInfo::Aslt;
    else if (instruction == "sltu") arguments = InstructionArgInfo::Asltu;
    else if (instruction == "sub") arguments = InstructionArgInfo::Asub;
    else if (instruction == "subu") arguments = InstructionArgInfo::Asubu;
    else if (instruction == "jr") arguments = InstructionArgInfo::Ajr;

    else if (instruction == "addi") arguments = InstructionArgInfo::Aaddi;
    else if (instruction == "addiu") arguments = InstructionArgInfo::Aaddiu;
    else if (instruction == "andi") arguments = InstructionArgInfo::Aandi;
    else if (instruction == "ori") arguments = InstructionArgInfo::Aori;
    else if (instruction == "slti") arguments = InstructionArgInfo::Aslti;
    else if (instruction == "sltiu") arguments = InstructionArgInfo::Asltiu;
    else if (instruction == "beq") arguments = InstructionArgInfo::Abeq;
    else if (instruction == "bne") arguments = InstructionArgInfo::Abne;
    else if (instruction == "sll") arguments = InstructionArgInfo::Asll;
    else if (instruction == "srl")  arguments = InstructionArgInfo::Asrl;

    else if (instruction == "j") arguments = InstructionArgInfo::Aj;
    else if (instruction == "jal")  arguments = InstructionArgInfo::Ajal;

    else if (instruction == "move") arguments = InstructionArgInfo::Amove;
    else if (instruction == "li") arguments = InstructionArgInfo::Ali;
    //else if (instruction == "lw") arguments = InstructionArgInfo::Alw;
    //else if (instruction == "la") arguments = InstructionArgInfo::Ala;
    else if (instruction == "blt") arguments = InstructionArgInfo::Ablt;
    else if (instruction == "ble") arguments = InstructionArgInfo::Able;
    else if (instruction == "bgt") arguments = InstructionArgInfo::Abgt;
    else if (instruction == "bge") arguments = InstructionArgInfo::Abge;
    else arguments = 0x00;

    result.total = arguments >> 6;
    result.registers = (arguments >> 4) & 0x03;
    result.immediates = (arguments >> 2) & 0x03;
    result.addresses = arguments & 0x03;

    return result;
}

argumentInfo GrammarChecker::getExpressionArguments(const std::string& currentExpression){
    argumentInfo result;
    result.total = std::count(currentExpression.begin(), currentExpression.end(), ',') + 1;
    result.registers = std::count(currentExpression.begin(), currentExpression.end(), '$');
    result.addresses = std::count(currentExpression.begin(), currentExpression.end(), '&');
    result.immediates = result.total - result.registers - result.addresses;
    return result;
}
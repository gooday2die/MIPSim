//
// @file : GrammarChecker.cpp
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : A file that implements all member functions for class GrammarChecker
// @date: 2022-03-12

#include "GrammarChecker.h"

/**
 * A constructor member function for GrammarChecker
 * @param argAllBranches the pointer of allBranches
 */
GrammarChecker::GrammarChecker(std::map<std::string, uint32_t>* argAllBranches) {
    this->allBranches = argAllBranches;
}

/**
 * A member function that checks if current branch name is valid.
 * @param curLine the string object to find out if the branch name is valid
 * @param allBranchNames all branch's names
 */
void GrammarChecker::checkBranchName(const std::string& curLine) {
    uint32_t originalValue = 0;
    try {
        if (curLine.find(32) != std::string::npos) { // check if branch as any whitespaces
            throw BranchExceptions::whitespaceNameException();
        } else if (curLine.empty()) { // check if the branch name was empty
            throw BranchExceptions::emptyNameException();
        }
        originalValue = this->branchDeclarationCount.at(curLine);
        if (originalValue >= 2){ // check if the branch was used before
            throw BranchExceptions::duplicateNameException();
        }
    } catch(std::out_of_range const& ex){ // if exception that means it was not generated before.
        this->branchDeclarationCount.insert(std::pair<std::string, uint32_t>(curLine, originalValue + 1));
    }
}

/**
 * A member function for GrammarChecker that checks if an expression is valid in syntax.
 * This currently checks argument validity.
 * @param currentExpression the string object that represent current expression
 * @param allBranchNames all branches
 */
void GrammarChecker::checkExpressionValidity(const std::string& currentExpression) {
    checkArgumentsValidity(currentExpression);
}

/**
 * A member function for GrammarChecker that checks if expression's arguments were valid in type and order
 * @param currentExpression current expression string to check if it is valid or not
 */
void GrammarChecker::checkArgumentsValidity(const std::string &currentExpression) {
    std::string space_delimiter = " ";
    std::vector<std::string> words{};
    std::string copiedExpression = currentExpression;

    size_t pos = 0;
    while ((pos = copiedExpression.find(space_delimiter)) != std::string::npos) { // split expression with whitespace
        words.push_back(copiedExpression.substr(0, pos));
        copiedExpression.erase(0, pos + space_delimiter.length());
    }

    std::string instructionMnemonic = words[0]; // split words
    argumentInfo instructionInfo = getArgumentInfo(words[0]); // get the instruction info that is being used
    argumentInfo expressionArguments = getExpressionArguments(currentExpression); // get the expression arguments that was entered

    /**
     * The GrammarChecker has enum InstructionArgInfo which includes the format of each instructions
     * If the instruction was not found, it is returned as 0x00.
     */

    if (instructionInfo.total == 0) throw ExpressionExceptions::unknownInstructionMnemonicException();
    // When it was unrecognizable instruction.
    else{
        uint8_t totalArgProcessed = 0;
        // check instruction's arguments were correct
        if ((instructionInfo.total == expressionArguments.total) && // check if total arguments were the correct
        (instructionInfo.addresses == expressionArguments.addresses) && // check if total addresses were correct
        (instructionInfo.registers == expressionArguments.registers) && // check if registers were correct
        (instructionInfo.immediates == expressionArguments.immediates)){ // check if immediates were correct
            for (uint8_t i = 1 ; i < instructionInfo.registers + 1 ; i++) { // check if registers were correct
                if (!isValidRegister(words[i])) throw ExpressionExceptions::unknownRegisterException();
                totalArgProcessed++;
            }

            for (uint8_t i = 0 ; i < instructionInfo.immediates ; i++){ // check if immediates were correct
                if (!isValidImmediate(words[i + 1 + instructionInfo.registers])) throw ExpressionExceptions::invalidImmediateValueException();
                totalArgProcessed++;
            }

            for (uint8_t i = 0 ; i < instructionInfo.addresses ; i++){ // check if addresses were correct
                if (!isValidAddress(words[i + 1 + instructionInfo.registers + instructionInfo.immediates])) throw ExpressionExceptions::invalidAddressValueException();
                totalArgProcessed++;
            }
        } else throw ExpressionExceptions::invalidArgumentException();
    }
}

/**
 * A member function for GrammarChecker that checks if a register is a valid register
 * @param curArgument current register argument from expression to check validity
 * @return true if valid, false if not
 */
bool GrammarChecker::isValidRegister(const std::string & curArgument) {
    std::string argument = curArgument;
    if (std::count(argument.begin(), argument.end(), '$') != 1) // if this was not a register
        return false; // throw exception
    else{ // if this was a register
        try{ // try checking if the register was correct
            argument.erase(std::remove(argument.begin(), argument.end(), '$'), argument.end());
            argument.erase(std::remove(argument.begin(), argument.end(), ','), argument.end());
            uint32_t translatedInt = std::stoi(argument); // stoi into integer and check if it was valid register index
            if ((translatedInt > 31) || (translatedInt < 0)) return false; // check register's range
        }
        catch (std::invalid_argument const& ex){ // if it cannot be processed using stoi, it is unknown register
            return false;
        }
    }
    return true;
}

/**
 * A member function for GrammarChecker that checks if an immediate is valid
 * @param curArgument current immediate value from expression to check validity
 * @return true if valid, false if not
 */
bool GrammarChecker::isValidImmediate(const std::string& curArgument){
    const std::string& argument = curArgument;
    try{
        std::stoi(argument);
        return true;
    } catch (std::invalid_argument const& ex){ // if it cannot be 'stoi'ed it means that it is not integer
        return false;
    }
}

/**
 * A member function for GrammarChecker that checks if a branch's address is valid
 * Address is represented as '&' with instruction's index (for example: &3)
 * @param curArgument current branch's address value.
 * @return returns true if valid, false if not
 */
bool GrammarChecker::isValidBranchAddress(const std::string & curArgument) {
    try {
        std::string argument = curArgument;
        argument.erase(std::remove(argument.begin(), argument.end(), '&'), argument.end());
        uint32_t addrIndex = std::stoi(argument);

        bool result = std::any_of(this->allBranches->begin(), this->allBranches->end(), [&addrIndex](auto const &x) {
            if (x.second == addrIndex) return true;
        });
        return result;
    } catch(std::exception const& ex){
        throw ExpressionExceptions::invalidAddressValueException();
    }
}

/**
 * A member function for GrammarChecker that checks if an address is valid.
 * This member function currently supports checking branches. More features will be added to this member function.
 * @param curArgument current address value from expression to check validity
 * @return true if valid, false if not
 */
bool GrammarChecker::isValidAddress(const std::string & curArgument) {
    //std::cout << curArgument << "is valid branch name : " << isBranchName(curArgument) << std::endl;
    const std::string& argument = curArgument;
    if (isValidBranchAddress(argument)) return true;
    return false;
}

/**
 * A member function for GrammarChecker that retrieves if a branch's name is duplicate or not
 * @param branchName the string object that represents branch's name
 * @return true if it is a duplicate named branch, false if not
 */
bool GrammarChecker::isBranchName(const std::string& branchName) {
    bool result = std::any_of(this->allBranches->begin(), this->allBranches->end(), [&branchName](auto const& x){
        if (x.first == branchName) return true;
    });
    return result;
}

/**
 * A member function for GrammarChecker that retrieves an argument's original argument sets
 * @param instruction the string object that represents instruction
 * @return returns argumentInfo type value that represents instruction arguments
 */
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

/**
 * A member function that gets current expression's arguments
 * @param currentExpression the string object to find out current arguments
 * @return returns argumentInfo type value that represents arguments from expression
 */
argumentInfo GrammarChecker::getExpressionArguments(const std::string& currentExpression){
    argumentInfo result;
    result.total = std::count(currentExpression.begin(), currentExpression.end(), ',') + 1;
    result.registers = std::count(currentExpression.begin(), currentExpression.end(), '$');
    result.addresses = std::count(currentExpression.begin(), currentExpression.end(), '&');
    result.immediates = result.total - result.registers - result.addresses;
    return result;
}
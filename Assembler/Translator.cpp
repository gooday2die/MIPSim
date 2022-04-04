//
// @file : Translator.cpp
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : A file that implements all member functions for class Translator
//

#include "Translator.h"

/**
 * A constructor member function for class Translator.
 * This member function initializes this class by inserting all values into maps for future translation.
 */
Translator::Translator(uint32_t** argRegisters, uint32_t* argPc) {
    this->registers = argRegisters;
    this->pc = argPc;

    this->registerMnemonics.insert(pair<string, uint8_t>("zero",0));
    this->registerMnemonics.insert(pair<string, uint8_t>("at", 1));
    this->registerMnemonics.insert(pair<string, uint8_t>("v0", 2));
    this->registerMnemonics.insert(pair<string, uint8_t>("v1", 3));
    this->registerMnemonics.insert(pair<string, uint8_t>("a0", 4));
    this->registerMnemonics.insert(pair<string, uint8_t>("a1", 5));
    this->registerMnemonics.insert(pair<string, uint8_t>("a2", 6));
    this->registerMnemonics.insert(pair<string, uint8_t>("a3", 7));
    this->registerMnemonics.insert(pair<string, uint8_t>("t0", 8));
    this->registerMnemonics.insert(pair<string, uint8_t>("t1", 9));
    this->registerMnemonics.insert(pair<string, uint8_t>("t2", 10));
    this->registerMnemonics.insert(pair<string, uint8_t>("t3", 11));
    this->registerMnemonics.insert(pair<string, uint8_t>("t4", 12));
    this->registerMnemonics.insert(pair<string, uint8_t>("t5", 13));
    this->registerMnemonics.insert(pair<string, uint8_t>("t6", 14));
    this->registerMnemonics.insert(pair<string, uint8_t>("t7", 15));
    this->registerMnemonics.insert(pair<string, uint8_t>("s0", 16));
    this->registerMnemonics.insert(pair<string, uint8_t>("s1", 17));
    this->registerMnemonics.insert(pair<string, uint8_t>("s2", 18));
    this->registerMnemonics.insert(pair<string, uint8_t>("s3", 19));
    this->registerMnemonics.insert(pair<string, uint8_t>("s4", 20));
    this->registerMnemonics.insert(pair<string, uint8_t>("s5", 21));
    this->registerMnemonics.insert(pair<string, uint8_t>("s6", 22));
    this->registerMnemonics.insert(pair<string, uint8_t>("s7", 23));
    this->registerMnemonics.insert(pair<string, uint8_t>("t8", 24));
    this->registerMnemonics.insert(pair<string, uint8_t>("t9", 25));
    this->registerMnemonics.insert(pair<string, uint8_t>("k0", 26));
    this->registerMnemonics.insert(pair<string, uint8_t>("k1", 27));
    this->registerMnemonics.insert(pair<string, uint8_t>("gp", 28));
    this->registerMnemonics.insert(pair<string, uint8_t>("sp", 29));
    this->registerMnemonics.insert(pair<string, uint8_t>("fp", 30));
    this->registerMnemonics.insert(pair<string, uint8_t>("ra", 31));

    this->instructionMnemonics.insert(pair<string, uint32_t>("add", 0x00000020));
    this->instructionMnemonics.insert(pair<string, uint32_t>("addi", 0x20000000));
    this->instructionMnemonics.insert(pair<string, uint32_t>("addiu", 0x24000000));
    this->instructionMnemonics.insert(pair<string, uint32_t>("addu",  0x00000021));
    this->instructionMnemonics.insert(pair<string, uint32_t>("and", 0x00000024));
    this->instructionMnemonics.insert(pair<string, uint32_t>("andi", 0x30000000));
    this->instructionMnemonics.insert(pair<string, uint32_t>("beq", 0x10000000));
    this->instructionMnemonics.insert(pair<string, uint32_t>("bne", 0x14000000));
    this->instructionMnemonics.insert(pair<string, uint32_t>("j", 0x08000000));
    this->instructionMnemonics.insert(pair<string, uint32_t>("jal", 0x0c000000));
    this->instructionMnemonics.insert(pair<string, uint32_t>("jr", 0x00000008));
    this->instructionMnemonics.insert(pair<string, uint32_t>("nor", 0x00000027));
    this->instructionMnemonics.insert(pair<string, uint32_t>("or", 0x00000025));
    this->instructionMnemonics.insert(pair<string, uint32_t>("ori", 0x34000000));
    this->instructionMnemonics.insert(pair<string, uint32_t>("slt", 0x0000002a));
    this->instructionMnemonics.insert(pair<string, uint32_t>("slti", 0x28000000));
    this->instructionMnemonics.insert(pair<string, uint32_t>("sltiu", 0x2c000000));
    this->instructionMnemonics.insert(pair<string, uint32_t>("sltu", 0x0000002b));
    this->instructionMnemonics.insert(pair<string, uint32_t>("sll", 0x00000000));
    this->instructionMnemonics.insert(pair<string, uint32_t>("srl", 0x00000002));
    this->instructionMnemonics.insert(pair<string, uint32_t>("sub", 0x00000022));
    this->instructionMnemonics.insert(pair<string, uint32_t>("subu", 0x00000023));
    this->instructionMnemonics.insert(pair<string, uint32_t>("lui", 0x3c000000));

    this->pseudoInstructionExpressionCounts.insert(pair<string, uint8_t>("move", 1));
    this->pseudoInstructionExpressionCounts.insert(pair<string, uint8_t>("li", 1));
    this->pseudoInstructionExpressionCounts.insert(pair<string, uint8_t>("blt", 2));
    this->pseudoInstructionExpressionCounts.insert(pair<string, uint8_t>("ble", 2));
    this->pseudoInstructionExpressionCounts.insert(pair<string, uint8_t>("bgt", 2));
    this->pseudoInstructionExpressionCounts.insert(pair<string, uint8_t>("bge", 2));
}

/**
 * A member function for class Translator that translates given register string into register index value
 * @param registerString the string that represents register's index or mnemonic if the register.
 * @return returns uint8_t type that represents register's index.
 */
uint8_t Translator::translateRegister(const string& registerString) {
    string copied = registerString;
    copied = regex_replace(copied, regex("\\$"), "");
    uint8_t registerIndex;
    try{
        registerIndex = stoi(copied);
    } catch (const invalid_argument& ex) {
        try{
            registerIndex = this->registerMnemonics.at(copied);
        } catch (const out_of_range& ex) {
            throw TranslatorExceptions::cannotFindRegisterIndexException();
        }
    }
    return registerIndex;
}

/**
 * A member function for class Translator that translates given immediate string into immediate value.
 * @param immediateString the string that represents immediate value.
 * @return uint16_t type that represents immediate.
 */
uint16_t Translator::translateImmediate(const string& immediateString) {
    try{
        return stoi(immediateString);
    } catch (const invalid_argument& ex) {
        throw TranslatorExceptions::cannotTranslateImmediateException();
    }
}

/**
 * A member function for class Translator that translates label string into address value.
 * This member function returns a pair of two uint32_t addresses that represent the address of label.
 * pair<uint32_t, uint32_t>(Index of instruction, relative address or shifted address for jumps and bne operations)
 * @param labelName the string object that represents label name
 * @return return pair of uint32_t that represent addresses.
 */
pair<uint32_t, uint32_t>Translator::translateLabel(const string& labelName, const string& instructionMnemonic) {
    try{
        if ((instructionMnemonic == "beq") || (instructionMnemonic == "bne")) {
            int16_t relativeAddress = this->textSectionLabel.at(labelName) - this->curTextSectionExpressionIndex;
            return {this->textSectionLabel.at(labelName), (relativeAddress - 2 * (relativeAddress < 0)) & (0xFFFF)}; // if neg, -2 to the result.
        } else if ((instructionMnemonic == "j") || (instructionMnemonic == "jal")) {
            uint32_t returnAddr = 0x00400000 + (4 * this->textSectionLabel.at(labelName));
            returnAddr = returnAddr >> 2;
            return {this->textSectionLabel.at(labelName), returnAddr};
        }
        else{
            cout << "CANNOT PROCESS LABEL " << endl;
            return {0, 0};
        }
    } catch (const range_error& ex) {
        throw TranslatorExceptions::cannotFindLabelNameException();
    }
}

/**
 * A member function that prints out all labels and its addresses
 */
void Translator::printLabels() {
    for (auto const& x : this->textSectionLabel) {
        cout << "Branch Name : " << x.first << " @ ";
        printf("0x%08x\n", (0x00400000 + 4 *x.second));
    }
}

/**
 * A member function that scans all labels and sets address for the label map
 * @param token the first token for current expression
 * @param expressionString the string object that represents current expression.
 */
void Translator::scanLabelAddresses(const Tokens& token, const string& expressionString) {
    switch(token) {
        case tSection: {
            if ("text." == expressionString) this->currentSectionType = 1;
            else if ("data." == expressionString) this->currentSectionType = 2;
            break;
        }
        case tLabelDeclaration:{
            string labelName = regex_replace(expressionString, regex(":"), "");
            if (this->currentSectionType == 1)
                this->textSectionLabel.insert({labelName, this->textSectionExpressionCount});
            else
                this->dataSectionLabel.insert({labelName, this->dataSectionExpressionCount});
            break;
        }
        case tInstructionMnemonic:
        case tSyscall:
            textSectionExpressionCount++;
            break;
        case tDataDefinition:
            dataSectionExpressionCount++;
            break;
        case tPseudoInstruction:
            textSectionExpressionCount += this->pseudoInstructionExpressionCounts.at(expressionString);
            break;
        case tUnknown:
        case tRegister:
        case tImmediate:
        case tDefinedLabel:
        case tString:
            break;
    }
}

/**
 * A member function that gets total label's count
 * @return uint16_t type that represents total count of declared labels.
 */
uint16_t Translator::getLabelCount() {
    return this->textSectionLabel.size() + this->dataSectionLabel.size();
}

/**
 * A member function for class Translator that translates expression string and token queue into a Expression object.
 * This member function translates expressions with only tInstructionMnemonic. Syscall and pseudo instruction must be
 * translated using translate member function.
 * @param tokenQueue the queue of tokens for this expression
 * @param expressionString the string object that represents expression
 * @return returns Expression object that represents current expression.
 */
Expression Translator::translateNormalExpression(const queue<Tokens>& tokenQueue, const string& expressionString) {
    string copiedExpressionString = expressionString;
    queue<Tokens> copiedTokenQueue = tokenQueue;
    vector<uint32_t*> instructionArgs;
    uint32_t machineCode;

    string space_delimiter = " ";
    vector<string> words{};
    size_t pos;
    while ((pos = copiedExpressionString.find(space_delimiter)) != string::npos) { // split expression with whitespace
        words.push_back(copiedExpressionString.substr(0, pos));
        copiedExpressionString.erase(0, pos + space_delimiter.length());
    }
    // cout << expressionString << " -> ";
    string instructionMnemonic = words[0]; // parse instruction mnemonic
    try {
        machineCode = this->instructionMnemonics.at(instructionMnemonic);
        uint8_t curArgumentCount = 1; // for index of current argument
        uint8_t curRegisterCount = 0; // for index of current register
        copiedTokenQueue.pop();

        while (!copiedTokenQueue.empty()) { // pop and translate each argument strings.
            Tokens currentToken = copiedTokenQueue.front();
            string currentArgument = words[curArgumentCount];
            copiedTokenQueue.pop();
            curArgumentCount++;
            if (currentToken == Tokens::tRegister) {
                uint8_t registerValue = this->translateRegister(currentArgument);
                instructionArgs.emplace_back((*this->registers) + registerValue);
                //printf("Register : %d", this->registers[registerValue]);
                machineCode = machineCode | (registerValue << (21 - curRegisterCount * 5));
                curRegisterCount++;
                //cout << "Register $" << to_string(registerValue) << " ";
            } else if (currentToken == Tokens::tImmediate) {
                uint32_t immediateValue = 0x0000FFFF & this->translateImmediate(currentArgument);
                machineCode = machineCode | (immediateValue);
                auto* immediateAddress = new uint32_t(immediateValue);
                instructionArgs.emplace_back(immediateAddress);
                //cout << "Immediate Value " << to_string(immediateValue) << " ";
            } else if (currentToken == Tokens::tDefinedLabel) {
                uint32_t addressValue = this->translateLabel(currentArgument, instructionMnemonic).second;
                uint32_t instructionIndex = this->translateLabel(currentArgument, instructionMnemonic).first;
                instructionArgs.emplace_back(&instructionIndex);
                machineCode = machineCode | (addressValue);
                //printf("Address Value 0x%08x", addressValue);
            } else {
                throw TranslatorExceptions::unexpectedInstructionArgumentTokenException();
            }
        }
        this->curTextSectionExpressionIndex = this->curTextSectionExpressionIndex + 1;
        instructionArgs.emplace_back(this->pc);
        Expression result = Expression(instructionArgs, expressionString, instructionMnemonic, machineCode);
        return result;
    } catch (const out_of_range& ex) {
        throw TranslatorExceptions::cannotFindInstructionMnemonicException();
    }
}

/**
 * A member function for class Translator that translates pseudo instructions into normal expressions.
 * @param tokenQueue the queue of tokens
 * @param expressionString the string object that represents expression.
 * @return returns a vector of Expressions that corresponds to pseudo instructions translated into normal expressions.
 */
vector<Expression> Translator::translatePseudoInstruction(const queue<Tokens>& tokenQueue, const string& expressionString) {
    string space_delimiter = " ";
    vector<string> words{};
    vector<Expression> returnVector;
    string copiedExpressionString = expressionString;
    size_t pos;

    while ((pos = copiedExpressionString.find(space_delimiter)) != string::npos) { // split expression with whitespace
        words.push_back(copiedExpressionString.substr(0, pos));
        copiedExpressionString.erase(0, pos + space_delimiter.length());
    }
    if (words[0] == "move") {
        /// move pseudo-instruction: addu $t0, $zero, $s0
        queue<Tokens> tmpTokenQueue;
        tmpTokenQueue.push(Tokens::tInstructionMnemonic);
        tmpTokenQueue.push(Tokens::tRegister);
        tmpTokenQueue.push(Tokens::tRegister);
        tmpTokenQueue.push(Tokens::tRegister);

        Expression result = this->translateNormalExpression(tmpTokenQueue, "addu " + words[1] + " $0 " + words[2] + " ");
        returnVector.emplace_back(result);
    } else if(words[0] == "li") {
        /// li pseudo-instruction: ori $s0, $zero, immediate
        queue<Tokens> tmpTokenQueue;
        tmpTokenQueue.push(Tokens::tInstructionMnemonic);
        tmpTokenQueue.push(Tokens::tRegister);
        tmpTokenQueue.push(Tokens::tRegister);
        tmpTokenQueue.push(Tokens::tImmediate);

        Expression result = this->translateNormalExpression(tmpTokenQueue, "ori $0 " + words[1] + " " + words[2] + " ");
        returnVector.emplace_back(result);
    } else if(words[0] == "blt") {
        /// blt pseudo-instruction:
        /// slt $t0, $t1, $at
        /// bne $at, $zero, branch
        queue<Tokens> tmpTokenQueue1;
        queue<Tokens> tmpTokenQueue2;
        tmpTokenQueue1.push(Tokens::tInstructionMnemonic);
        tmpTokenQueue1.push(Tokens::tRegister);
        tmpTokenQueue1.push(Tokens::tRegister);
        tmpTokenQueue1.push(Tokens::tRegister);

        tmpTokenQueue2.push(Tokens::tInstructionMnemonic);
        tmpTokenQueue2.push(Tokens::tRegister);
        tmpTokenQueue2.push(Tokens::tRegister);
        tmpTokenQueue2.push(Tokens::tDefinedLabel);

        Expression result = this->translateNormalExpression(tmpTokenQueue1, "slt " + words[1] + " " + words[2] + " $at ");
        returnVector.emplace_back(result);
        result = this->translateNormalExpression(tmpTokenQueue2, "bne $at $zero " + words[3] + " ");
        returnVector.emplace_back(result);
    } else if(words[0] == "ble") {
        /// ble pseudo-instruction:
        /// slt $t1, $t0, $at
        /// beq $at, $zero, branch
        queue<Tokens> tmpTokenQueue1;
        queue<Tokens> tmpTokenQueue2;
        tmpTokenQueue1.push(Tokens::tInstructionMnemonic);
        tmpTokenQueue1.push(Tokens::tRegister);
        tmpTokenQueue1.push(Tokens::tRegister);
        tmpTokenQueue1.push(Tokens::tRegister);

        tmpTokenQueue2.push(Tokens::tInstructionMnemonic);
        tmpTokenQueue2.push(Tokens::tRegister);
        tmpTokenQueue2.push(Tokens::tRegister);
        tmpTokenQueue2.push(Tokens::tDefinedLabel);

        Expression result = this->translateNormalExpression(tmpTokenQueue1, "slt " + words[2] + " " + words[1] + " $at ");
        returnVector.emplace_back(result);
        result = this->translateNormalExpression(tmpTokenQueue2, "beq $at $zero " + words[3] + " ");
        returnVector.emplace_back(result);
    } else if(words[0] == "bgt") {
        /// bgt pseudo-instruction:
        /// slt $t1, $t0, $at
        /// bne $at, $zero, branch
        queue<Tokens> tmpTokenQueue1;
        queue<Tokens> tmpTokenQueue2;
        tmpTokenQueue1.push(Tokens::tInstructionMnemonic);
        tmpTokenQueue1.push(Tokens::tRegister);
        tmpTokenQueue1.push(Tokens::tRegister);
        tmpTokenQueue1.push(Tokens::tRegister);

        tmpTokenQueue2.push(Tokens::tInstructionMnemonic);
        tmpTokenQueue2.push(Tokens::tRegister);
        tmpTokenQueue2.push(Tokens::tRegister);
        tmpTokenQueue2.push(Tokens::tDefinedLabel);

        Expression result = this->translateNormalExpression(tmpTokenQueue1, "slt " + words[2] + " " + words[1] + " $at ");
        returnVector.emplace_back(result);
        result = this->translateNormalExpression(tmpTokenQueue2, "bne $at $zero " + words[3] + " ");
        returnVector.emplace_back(result);
    } else if(words[0] == "bge") {
        /// bge pseudo-instruction:
        /// slt $t1, $t0, $at
        /// beq $at, $zero, branch
        queue<Tokens> tmpTokenQueue1;
        queue<Tokens> tmpTokenQueue2;
        tmpTokenQueue1.push(Tokens::tInstructionMnemonic);
        tmpTokenQueue1.push(Tokens::tRegister);
        tmpTokenQueue1.push(Tokens::tRegister);
        tmpTokenQueue1.push(Tokens::tRegister);

        tmpTokenQueue2.push(Tokens::tInstructionMnemonic);
        tmpTokenQueue2.push(Tokens::tRegister);
        tmpTokenQueue2.push(Tokens::tRegister);
        tmpTokenQueue2.push(Tokens::tDefinedLabel);

        Expression result = this->translateNormalExpression(tmpTokenQueue1,
                                                            "slt " + words[1] + " " + words[2] + " $at ");
        returnVector.emplace_back(result);
        result = this->translateNormalExpression(tmpTokenQueue2, "beq $at $zero " + words[3] + " ");
        returnVector.emplace_back(result);
    } else {
        throw TranslatorExceptions::unknownPseudoInstruction();
    }
    return returnVector;
}

/**
 * A member function for class Translator that translates syscall expressions
 * @param tokenQueue the queue of tokens
 * @param expressionString the string that represent expression
 * @return returns Expression object that represents syscall.
 */
Expression Translator::translateSyscall(const queue<Tokens>& tokenQueue, const string& expressionString) {
    vector<uint32_t*> argVector;
    argVector.emplace_back(*this->registers + 2); // get $v0
    argVector.emplace_back(*this->registers + 4); // get $a0

    syscall_ instruction = syscall_(argVector);
    Expression expression = Expression(argVector, "syscall", "syscall", 0x0000000C);
    return expression;
}

/**
 * A member function for class Translator that translates each expression and expression strings into vector of expressions.
 * This member function returns vector of expressions since some pseudo instructions need multiple instructions.
 * @param tokenQueue queue of tokens
 * @param expressionString the string object that represents current expression
 * @return returns vector of Expression objects for current expression.
 */
pair<uint8_t, vector<Expression>> Translator::translate(const queue<Tokens>& tokenQueue, const string& expressionString) {
    queue<Tokens> copiedTokenQueue = tokenQueue;
    vector<Expression> returnVector;

    Tokens instructionToken = copiedTokenQueue.front();
    copiedTokenQueue.pop();

    switch (instructionToken) {
        case tSection: {
            if ("text." == expressionString) this->currentSectionType = 1;
            else if ("data." == expressionString) this->currentSectionType = 2;
            break;
        }
        case tLabelDeclaration:{ // we have already set all label's addresses using scanLabelAddresses. So skip
            return {1, returnVector};
            break;
        }
        case tInstructionMnemonic:{ // when this was an instruction mnemonic then process as it should be
            returnVector.emplace_back(this->translateNormalExpression(tokenQueue, expressionString));
            return {1, returnVector};
        }
        case tPseudoInstruction: {
            return {1, this->translatePseudoInstruction(tokenQueue, expressionString)};
        }
        case tSyscall:{
            returnVector.emplace_back(this->translateSyscall(tokenQueue, expressionString));
            return {1, returnVector};
        }
        case tUnknown:
        case tDefinedLabel:
        case tDataDefinition:
        case tRegister:
        case tString:
        case tImmediate:
            throw TranslatorExceptions::unexpectedInstructionTokenTypeException();
    }
    return {-1, returnVector};
}
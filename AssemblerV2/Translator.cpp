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
Translator::Translator() {
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
    copied = regex_replace(copied, regex("\\$"), ""); // need to have \\$ as regex since $ is a regex
    uint8_t registerIndex;
    try{
        registerIndex = stoi(copied);
    } catch (const invalid_argument& ex){
        try{
            registerIndex = this->registerMnemonics.at(copied);
        } catch (const out_of_range& ex){
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
    } catch (const invalid_argument& ex){
        throw TranslatorExceptions::cannotTranslateImmediateException();
    }
}

/**
 * A member function that translates label into address
 * @param labelName the string object that represents label name
 * @return returns uint16_t type of expression's index.
 */
uint16_t Translator::translateLabel(const string& labelName) {
    try{
        return this->labelAddresses.at(labelName);
    } catch (const range_error& ex){
        throw TranslatorExceptions::cannotFindLabelNameException();
    }
}

/**
 * A member function that prints out all labels and its addresses
 */
void Translator::printLabels() {
    for (auto const& x : this->labelAddresses)
        cout << "Label Name : " << x.first << " @ " << to_string(x.second) << endl;
}

/**
 * A member function that scans all labels and sets address for the label map
 * @param token the first token for current expression
 * @param expressionString the string object that represents current expression.
 */
void Translator::scanLabelAddresses(const Tokens& token, const string& expressionString) {
    switch(token){
        case tSection: {
            if ("text." == expressionString) this->currentSectionType = 1;
            else if ("data." == expressionString) this->currentSectionType = 2;
            break;
        }
        case tLabelDeclaration:{
            string labelName = regex_replace(expressionString, regex(":"), "");
            if (this->currentSectionType == 1) this->labelAddresses.insert(pair<string, uint32_t>(labelName, this->textSectionExpressionCount));
            else this->labelAddresses.insert(pair<string, uint32_t>(labelName, this->dataSectionExpressionCount));
            break;
        }
        case tInstructionMnemonic:
            textSectionExpressionCount++;
            break;
        case tDataDefinition:
            dataSectionExpressionCount++;
            break;
        case tPseudoInstruction:
            textSectionExpressionCount = textSectionExpressionCount + this->pseudoInstructionExpressionCounts.at(expressionString);
            break;
        case tUnknown:
        case tRegister:
        case tImmediate:
        case tDefinedLabel:
            break;
    }
}

/**
 * A member function that gets total label's count
 * @return uint16_t type that represents total count of declared labels.
 */
uint16_t Translator::getLabelCount() {
    return this->labelAddresses.size();
}

uint32_t Translator::translateNormalInstruction(const queue<Tokens>& tokenQueue, const string& expressionString) {
    string copiedExpressionString = expressionString;
    queue<Tokens> copiedTokenQueue = tokenQueue;
    uint32_t returnValue;

    string space_delimiter = " ";
    vector<string> words{};
    size_t pos;
    while ((pos = copiedExpressionString.find(space_delimiter)) != string::npos) { // split expression with whitespace
        words.push_back(copiedExpressionString.substr(0, pos));
        copiedExpressionString.erase(0, pos + space_delimiter.length());
    }
    cout << expressionString << " -> ";
    string instructionMnemonic = words[0]; // parse instruction mnemonic
    try {
        returnValue = this->instructionMnemonics.at(instructionMnemonic);
        uint8_t nthArgument = 1;
        uint8_t curRegisterCount = 0;
        copiedTokenQueue.pop();

        while (!copiedTokenQueue.empty()) { // pop and translate each argument strings.
            Tokens currentToken = copiedTokenQueue.front();
            string currentArgument = words[nthArgument];
            copiedTokenQueue.pop();
            nthArgument++;

            if (currentToken == Tokens::tRegister) {
                uint8_t registerValue = this->translateRegister(currentArgument);
                returnValue = returnValue | (registerValue << (21 - curRegisterCount * 5));
                curRegisterCount++;
                cout << "Register $" << to_string(registerValue) << " ";
            } else if (currentToken == Tokens::tImmediate) {
                uint16_t immediateValue = this->translateImmediate(currentArgument);
                returnValue = returnValue | (immediateValue);
                cout << "Immediate Value " << to_string(immediateValue) << " ";
            } else if (currentToken == Tokens::tDefinedLabel) {
                uint16_t addressValue = this->translateLabel(currentArgument);
                returnValue = returnValue | (addressValue);
                cout << "Address Value " << to_string(addressValue) << " ";
            } else {
                throw TranslatorExceptions::unexpectedInstructionArgumentTokenException();
            }
        }
    }
    catch (const out_of_range& ex) {
        throw TranslatorExceptions::cannotFindInstructionMnemonicException();
    }
    cout << endl;
    return returnValue;
}

/**
 * A member function for class Translator that translates the current expression with tokens into machine code
 * @param tokenQueue queue of tokens
 * @param expressionString the string object that represents current expression
 * @return returns uint32_t type of machine code that was translated from expression.
 */
vector<uint32_t> Translator::translate(const queue<Tokens>& tokenQueue, const string& expressionString) {
    queue<Tokens> copiedTokenQueue = tokenQueue;
    string copiedExpressionString = expressionString;
    vector<uint32_t> returnVector;

    Tokens instructionToken = copiedTokenQueue.front();
    copiedTokenQueue.pop();

    switch (instructionToken) {
        case tSection: {
            if ("text." == expressionString) this->currentSectionType = 1;
            else if ("data." == expressionString) this->currentSectionType = 2;
            break;
        }
        case tLabelDeclaration:{ // we have already set all label's addresses using scanLabelAddresses. So skip
            break;
        }
        case tInstructionMnemonic:{ // when this was an instruction mnemonic then process as it should be
            uint32_t returnValue;
            returnValue = this->translateNormalInstruction(tokenQueue, expressionString);
            returnVector.emplace_back(returnValue);
            break;
        }
        case tPseudoInstruction: {
            string space_delimiter = " ";
            vector<string> words{};
            vector<string> translatedPseudoInstruction;

            size_t pos;
            while ((pos = copiedExpressionString.find(space_delimiter)) != string::npos) { // split expression with whitespace
                words.push_back(copiedExpressionString.substr(0, pos));
                copiedExpressionString.erase(0, pos + space_delimiter.length());
            }

            string instruction = words[0];
            if (instruction == "move"){
                /// move pseudo-instruction: addu $t0, $zero, $s0
                queue<Tokens> tmpTokenQueue;
                tmpTokenQueue.push(Tokens::tInstructionMnemonic);
                tmpTokenQueue.push(Tokens::tRegister);
                tmpTokenQueue.push(Tokens::tRegister);
                tmpTokenQueue.push(Tokens::tRegister);

                uint32_t returnValue = this->translateNormalInstruction(tmpTokenQueue, "addu " + words[1] + " $0 " + words[2] + " ");
                returnVector.emplace_back(returnValue);

            } else if(instruction == "li"){
                /// li pseudo-instruction: ori $s0, $zero, immediate
                queue<Tokens> tmpTokenQueue;
                tmpTokenQueue.push(Tokens::tInstructionMnemonic);
                tmpTokenQueue.push(Tokens::tRegister);
                tmpTokenQueue.push(Tokens::tRegister);
                tmpTokenQueue.push(Tokens::tImmediate);

                uint32_t returnValue = this->translateNormalInstruction(tmpTokenQueue, "ori $0 " + words[1] + " " + words[2] + " ");
                returnVector.emplace_back(returnValue);

            } else if(instruction == "blt"){
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

                uint32_t returnValue = this->translateNormalInstruction(tmpTokenQueue1, "slt " + words[1] + " " + words[2] + " $at ");
                returnVector.emplace_back(returnValue);
                returnValue = this->translateNormalInstruction(tmpTokenQueue2, "bne $at $zero " + words[3] + " ");
                returnVector.emplace_back(returnValue);

            } else if(instruction == "ble"){
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

                uint32_t returnValue = this->translateNormalInstruction(tmpTokenQueue1, "slt " + words[2] + " " + words[1] + " $at ");
                returnVector.emplace_back(returnValue);
                returnValue = this->translateNormalInstruction(tmpTokenQueue2, "beq $at $zero " + words[3] + " ");
                returnVector.emplace_back(returnValue);

            } else if(instruction == "bgt"){
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

                uint32_t returnValue = this->translateNormalInstruction(tmpTokenQueue1, "slt " + words[2] + " " + words[1] + " $at ");
                returnVector.emplace_back(returnValue);
                returnValue = this->translateNormalInstruction(tmpTokenQueue2, "bne $at $zero " + words[3] + " ");
                returnVector.emplace_back(returnValue);

            } else if(instruction == "bge"){
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

                uint32_t returnValue = this->translateNormalInstruction(tmpTokenQueue1, "slt " + words[1] + " " + words[2] + " $at ");
                returnVector.emplace_back(returnValue);
                returnValue = this->translateNormalInstruction(tmpTokenQueue2, "beq $at $zero " + words[3] + " ");
                returnVector.emplace_back(returnValue);
            }
            break;
        }
        case tUnknown:
        case tDefinedLabel:
        case tDataDefinition:
        case tRegister:
        case tImmediate:
            throw TranslatorExceptions::unexpectedInstructionTokenTypeException();
    }
    return returnVector;
}
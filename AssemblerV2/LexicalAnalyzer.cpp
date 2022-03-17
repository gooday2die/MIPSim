//
// @file : LexicalAnalyzer.cpp
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : A file that implements all member functions for class LexicalAnalyzer
// @date: 2022-03-16

#include "LexicalAnalyzer.h"


/**
 * A constructor member function for class LexicalAnalyzer.
 * This member function will put all tokens in each attributes.
 * Also this member function will scan throughout all lines to look for labels and save them for future use.
 * @param argAllExpressions the map object that represents all expressions
 */
LexicalAnalyzer::LexicalAnalyzer(map<uint32_t, Expression> argAllExpressions) {
    this->allExpressions = move(argAllExpressions);

    this->sectionTokens.emplace_back(".text"); // section tokens
    this->sectionTokens.emplace_back(".data");

    this->registerTokens.emplace_back("$zero"); // register tokens
    this->registerTokens.emplace_back("$at");
    this->registerTokens.emplace_back("$v0");
    this->registerTokens.emplace_back("$v1");
    this->registerTokens.emplace_back("$a0");
    this->registerTokens.emplace_back("$a1");
    this->registerTokens.emplace_back("$a2");
    this->registerTokens.emplace_back("$a3");
    this->registerTokens.emplace_back("$t0");
    this->registerTokens.emplace_back("$t1");
    this->registerTokens.emplace_back("$t2");
    this->registerTokens.emplace_back("$t3");
    this->registerTokens.emplace_back("$t4");
    this->registerTokens.emplace_back("$t5");
    this->registerTokens.emplace_back("$t6");
    this->registerTokens.emplace_back("$t7");
    this->registerTokens.emplace_back("$s0");
    this->registerTokens.emplace_back("$s1");
    this->registerTokens.emplace_back("$s2");
    this->registerTokens.emplace_back("$s3");
    this->registerTokens.emplace_back("$s4");
    this->registerTokens.emplace_back("$s5");
    this->registerTokens.emplace_back("$s6");
    this->registerTokens.emplace_back("$s7");
    this->registerTokens.emplace_back("$t8");
    this->registerTokens.emplace_back("$t9");
    this->registerTokens.emplace_back("$k0");
    this->registerTokens.emplace_back("$k1");
    this->registerTokens.emplace_back("$gp");
    this->registerTokens.emplace_back("$sp");
    this->registerTokens.emplace_back("$fp");
    this->registerTokens.emplace_back("$ra");

    this->instructionTokens.emplace_back("add"); // instruction mnemonic tokens
    this->instructionTokens.emplace_back("addu");
    this->instructionTokens.emplace_back("and");
    this->instructionTokens.emplace_back("nor");
    this->instructionTokens.emplace_back("or");
    this->instructionTokens.emplace_back("slt");
    this->instructionTokens.emplace_back("sltu");
    this->instructionTokens.emplace_back("sub");
    this->instructionTokens.emplace_back("subu");
    this->instructionTokens.emplace_back("jr");
    this->instructionTokens.emplace_back("addi");
    this->instructionTokens.emplace_back("addiu");
    this->instructionTokens.emplace_back("andi");
    this->instructionTokens.emplace_back("ori");
    this->instructionTokens.emplace_back("slti");
    this->instructionTokens.emplace_back("sltiu");
    this->instructionTokens.emplace_back("beq");
    this->instructionTokens.emplace_back("bne");
    this->instructionTokens.emplace_back("sll");
    this->instructionTokens.emplace_back("srl");
    this->instructionTokens.emplace_back("j");
    this->instructionTokens.emplace_back("jal");
    this->instructionTokens.emplace_back("move");
    this->instructionTokens.emplace_back("li");
    this->instructionTokens.emplace_back("blt");
    this->instructionTokens.emplace_back("ble");
    this->instructionTokens.emplace_back("bgt");
    this->instructionTokens.emplace_back("la");
    this->instructionTokens.emplace_back("bge");

    this->dataDefinitionTokens.emplace_back(".word");
    this->dataDefinitionTokens.emplace_back(".half");
    this->dataDefinitionTokens.emplace_back(".byte");
    this->dataDefinitionTokens.emplace_back(".ascii");
    this->dataDefinitionTokens.emplace_back(".asciiz");

    this->scanLabelTokens();
}

/**
 * A member function for LexicalAnalyzer that finds out if current argument is section token
 * @param argumentString the string object that represents current argument
 * @return true if it is a section token, false if not
 */
bool LexicalAnalyzer::isSectionToken(const string& argumentString) {
    bool result = any_of(this->sectionTokens.begin(), this->sectionTokens.end(), [&argumentString](auto const &x) {
        if (x == argumentString) return true; return false;
    });
    return result;
}

/**
 * A member function for LexicalAnalyzer that finds out if current argument is label token
 * @param argumentString the string object that represents current argument
 * @return true if it is a label token, false if not
 */
bool LexicalAnalyzer::isLabelToken(const string& argumentString){
    return (count(argumentString.begin(), argumentString.end(), ':') == 1);
}

/**
 * A member function for LexicalAnalyzer that finds out if current argument is immediate token
 * @param argumentString the string object that represents current argument
 * @return true if it is a immediate token, false if not
 */
bool LexicalAnalyzer::isImmediateToken(const string& argumentString) {
    try{
        stoi(argumentString);
        return true;
    } catch(exception const& ex){
        return false;
    }
}

/**
 * A member function for LexicalAnalyzer that finds out if current argument is register token
 * @param argumentString the string object that represents current argument
 * @return true if it is a register token, false if not
 */
bool LexicalAnalyzer::isRegisterToken(const string& argumentString) {
    string copiedString = argumentString;
    try{
        if(count(argumentString.begin(), argumentString.end(), '$') != 1) return false;
        else {
            copiedString.erase(remove(copiedString.begin(), copiedString.end(), '$'), copiedString.end());
            uint8_t converted = stoi(copiedString);
            if ((converted > 0) && (converted < 31)) return true;
            else return false;
        }
    } catch (const exception& ex){
        bool result = any_of(this->registerTokens.begin(), this->registerTokens.end(), [&argumentString](auto const &x) {
            if (x == argumentString) return true; return false;
        });
        return result;
    }
}

/**
 * A member function for LexicalAnalyzer that finds out if current argument is mnemonic instruction token
 * @param argumentString the string object that represents current argument
 * @return true if it is a mnemonic instruction token, false if not
 */
bool LexicalAnalyzer::isMnemonicInstructionToken(const string& argumentString){
    bool result = any_of(this->instructionTokens.begin(), this->instructionTokens.end(), [&argumentString](auto const &x) {
        if (x == argumentString) return true; return false;
    });
    return result;
}

/**
 * A member function for LexicalAnalyzer that finds out if current argument is defined label token
 * @param argumentString the string object that represents current argument
 * @return true if it is a defined label token, false if not
 */
bool LexicalAnalyzer::isDefinedLabelToken(const string& argumentString) {
    bool result = any_of(this->allFoundLabels.begin(), this->allFoundLabels.end(), [&argumentString](auto const &x) {
        if (x == argumentString) return true; return false;
    });
    return result;
}

/**
 * A member function for LexicalAnalyzer that finds out if current argument is data definition token
 * @param argumentString the string object that represents current argument
 * @return true if it is a data definition token, false if not
 */
bool LexicalAnalyzer::isDataDefinitionToken(const string& argumentString){
    bool result = any_of(this->dataDefinitionTokens.begin(), this->dataDefinitionTokens.end(), [&argumentString](auto const &x) {
        if (x == argumentString) return true; return false;
    });
    return result;
}

/**
 * A member function for LexicalAnalyzer that scans through all expressions and look for labels.
 * When each labels were found, it is stored inside allFoundLabels vector.
 */
void LexicalAnalyzer::scanLabelTokens() {
    for (auto const& x : this->allExpressions){
        string expressionString = x.second.getExpressionString();
        if (count(expressionString.begin(), expressionString.end(), ':') == 1){
            const char* line = expressionString.c_str();
            uint16_t curPos = 0;
            while(line[curPos] != '\0'){
                if(line[curPos] == ':'){
                    this->allFoundLabels.emplace_back(expressionString.substr(0, curPos));
                    break;
                }
                else curPos++;
            }
        }
    }
}

/**
 * A member function for class LexicalAnalyzer that analyzes each tokens and generates a queue of tokens
 * @param expressionString the string object that represents expression that we would like to analyze tokens from
 * @return a pair that includes string and queue of tokens
 */
pair<string, queue<Tokens>> LexicalAnalyzer::analyze(const string& expressionString) {
    string copied = expressionString;
    queue<Tokens> resultQueue;
    pair<string, queue<Tokens>> result;

    if (copied.empty()) return result;
    string space_delimiter = " ";
    vector<string> words{};

    size_t pos = 0;
    while ((pos = copied.find(space_delimiter)) != string::npos) { // split expression with whitespace
        words.push_back(copied.substr(0, pos));
        copied.erase(0, pos + space_delimiter.length());
    }

    for (auto const &x: words) {
        if (this->isSectionToken(x)) resultQueue.push(Tokens::tSection);
        else if (this->isLabelToken(x)) resultQueue.push(Tokens::tLabel);
        else if (this->isRegisterToken(x)) resultQueue.push(Tokens::tRegister);
        else if (this->isImmediateToken(x)) resultQueue.push(Tokens::tImmediate);
        else if (this->isMnemonicInstructionToken(x)) resultQueue.push(Tokens::tInstructionMnemonic);
        else if (this->isDefinedLabelToken(x)) resultQueue.push(Tokens::tDefinedLabel);
        else if (this->isDataDefinitionToken(x)) resultQueue.push(Tokens::tDataDefinition);
        else resultQueue.push(Tokens::tUnknown);
    }

    result.first = words[0];
    result.second = resultQueue;

    return result;
}
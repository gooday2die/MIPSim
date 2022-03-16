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
LexicalAnalyzer::LexicalAnalyzer(std::map<uint32_t, Expression> argAllExpressions) {
    this->allExpressions = std::move(argAllExpressions);

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

    this->scanLabelTokens();
}

/**
 * A member function for LexicalAnalyzer that finds out if current argument is section token
 * @param argumentString the string object that represents current argument
 * @return true if it is a section token, false if not
 */
bool LexicalAnalyzer::isSectionToken(const std::string& argumentString) {
    bool result = std::any_of(this->sectionTokens.begin(), this->sectionTokens.end(), [&argumentString](auto const &x) {
        if (x == argumentString) return true; return false;
    });
    return result;
}

/**
 * A member function for LexicalAnalyzer that finds out if current argument is label token
 * @param argumentString the string object that represents current argument
 * @return true if it is a label token, false if not
 */
bool LexicalAnalyzer::isLabelToken(const std::string& argumentString){
    return (std::count(argumentString.begin(), argumentString.end(), ':') == 1);
}

/**
 * A member function for LexicalAnalyzer that finds out if current argument is immediate token
 * @param argumentString the string object that represents current argument
 * @return true if it is a immediate token, false if not
 */
bool LexicalAnalyzer::isImmediateToken(const std::string& argumentString) {
    try{
        std::stoi(argumentString);
        return true;
    } catch(std::exception const& ex){
        return false;
    }
}

/**
 * A member function for LexicalAnalyzer that finds out if current argument is register token
 * @param argumentString the string object that represents current argument
 * @return true if it is a register token, false if not
 */
bool LexicalAnalyzer::isRegisterToken(const std::string& argumentString) {
    std::string copiedString = argumentString;
    try{
        if(std::count(argumentString.begin(), argumentString.end(), '$') != 1) return false;
        else {
            copiedString.erase(std::remove(copiedString.begin(), copiedString.end(), '$'), copiedString.end());
            uint8_t converted = std::stoi(copiedString);
            if ((converted > 0) && (converted < 31)) return true;
            else return false;
        }
    } catch (const std::exception& ex){
        bool result = std::any_of(this->registerTokens.begin(), this->registerTokens.end(), [&argumentString](auto const &x) {
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
bool LexicalAnalyzer::isMnemonicInstructionToken(const std::string& argumentString){
    bool result = std::any_of(this->instructionTokens.begin(), this->instructionTokens.end(), [&argumentString](auto const &x) {
        if (x == argumentString) return true; return false;
    });
    return result;
}

/**
 * A member function for LexicalAnalyzer that finds out if current argument is defined label token
 * @param argumentString the string object that represents current argument
 * @return true if it is a defined label token, false if not
 */
bool LexicalAnalyzer::isDefinedLabelToken(const std::string& argumentString) {
    bool result = std::any_of(this->allFoundLabels.begin(), this->allFoundLabels.end(), [&argumentString](auto const &x) {
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
        std::string expressionString = x.second.getExpressionString();
        if (std::count(expressionString.begin(), expressionString.end(), ':') == 1){
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
 * A member function for LexicalAnalyzer that analyzes a single expression string using lexical analysis.
 * @param expressionString the string object that represents current expression.
 */
void LexicalAnalyzer::analyze(const std::string& expressionString) {
    std::string copied = expressionString;

    if (copied.empty()) return;
    std::string space_delimiter = " ";
    std::vector<std::string> words{};

    size_t pos = 0;
    while ((pos = copied.find(space_delimiter)) != std::string::npos) { // split expression with whitespace
        words.push_back(copied.substr(0, pos));
        copied.erase(0, pos + space_delimiter.length());
    }

    for(auto const& x : words){
        std::cout << x << " ";
        if (this->isSectionToken(x)) std::cout << "SECTION_TOKEN ";
        else if (this->isLabelToken(x)) std::cout << "LABEL_TOKEN ";
        else if (this->isRegisterToken(x)) std::cout << "REGISTER_TOKEN ";
        else if (this->isImmediateToken(x)) std::cout << "IMMEDIATE_TOKEN ";
        else if (this->isMnemonicInstructionToken(x)) std::cout << "MNEMONIC_TOKEN ";
        else if (this->isDefinedLabelToken(x)) std::cout << "DEFINED_LABEL_TOKEN";
        else std::cout << "UNKNOWN_TOKEN ";
    }
    std::cout << std::endl;
}
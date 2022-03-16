//
// @file : LexicalAnalyzer.h
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : A file that defines all attributes and member functions for class GrammarChecker
// @date: 2022-03-16

#ifndef MIPSIM_LEXICALANALYZER_H
#define MIPSIM_LEXICALANALYZER_H
#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <utility>

#include "Expression.h"

/**
 * A class that is for analyzing expressions using lexical analysis.
 */
class LexicalAnalyzer {
private:
    std::vector<std::string> allFoundLabels;
    std::vector<std::string> sectionTokens;
    std::vector<std::string> registerTokens;
    std::vector<std::string> instructionTokens;

    std::map<uint32_t, Expression> allExpressions;

    bool isSectionToken(const std::string&);
    bool isLabelToken(const std::string&);
    bool isRegisterToken(const std::string&);
    bool isImmediateToken(const std::string&);
    bool isMnemonicInstructionToken(const std::string&);
    bool isDefinedLabelToken(const std::string&);

    void scanLabelTokens();
public:
    explicit LexicalAnalyzer(std::map<uint32_t, Expression>);
    void analyze(const std::string&);
};


#endif //MIPSIM_LEXICALANALYZER_H

//
// @file : LexicalAnalyzer.
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : 
// @date: 2022-03-16

#ifndef MIPSIM_LEXICALANALYZER_H
#define MIPSIM_LEXICALANALYZER_H
#pragma once

#include <string>
#include <iostream>

class LexicalAnalyzer {
private:
    static bool isSectionToken(const std::string&);
    static bool isImmediateToken(const std::string&);
    static bool isLabelToken(const std::string&);
    static bool isRegisterToken(const std::string&);
    static std::string getLabelName(const std::string&);
    static std::string getSectionName(const std::string&);
public:
    static void analyze(const std::string&);
};


#endif //MIPSIM_LEXICALANALYZER_H

//
// @file : LexicalAnalyzer.h
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : A file that defines all attributes and member functions for class LexicalAnalyzer
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
#include <queue>

#include "Expression.h"
#include "Token.h"

using namespace std;

/**
 * A class that is for analyzing expressions using lexical analysis.
 */
class LexicalAnalyzer {
private:
    vector<string> allFoundLabels;
    vector<string> sectionTokens;
    vector<string> registerTokens;
    vector<string> instructionTokens;

    map<uint32_t, Expression> allExpressions;

    bool isSectionToken(const string&);
    bool isLabelToken(const string&);
    bool isRegisterToken(const string&);
    bool isImmediateToken(const string&);
    bool isMnemonicInstructionToken(const string&);
    bool isDefinedLabelToken(const string&);

    void scanLabelTokens();
public:
    explicit LexicalAnalyzer(map<uint32_t, Expression>);
    queue<Tokens> analyze(const string&);
};


#endif //MIPSIM_LEXICALANALYZER_H

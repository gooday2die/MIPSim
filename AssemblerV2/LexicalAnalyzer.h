//
// @file : LexicalAnalyzer.h
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : A file that defines all attributes and member functions for class LexicalAnalyzer
//

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
    vector<string> pseudoInstructionTokens;
    vector<string> dataDefinitionTokens;

    map<uint32_t, string> allExpressions;

    bool isSectionToken(const string&);
    bool isLabelToken(const string&);
    bool isRegisterToken(const string&);
    bool isImmediateToken(const string&);
    bool isMnemonicInstructionToken(const string&);
    bool isDefinedLabelToken(const string&);
    bool isDataDefinitionToken(const string&);
    bool isPseudoInstructionToken(const string&);

    void scanLabelTokens();
public:
    explicit LexicalAnalyzer(map<uint32_t, string>);
    pair<string, queue<Tokens>> analyze(const string&);
};


#endif //MIPSIM_LEXICALANALYZER_H

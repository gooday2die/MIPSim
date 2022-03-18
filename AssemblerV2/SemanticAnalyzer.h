//
// @file : SemanticAnalyzer.h
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : A file that defines all attributes and member functions for class SemanticAnalyzer
//

#ifndef MIPSIM_SEMANTICANALYZER_H
#define MIPSIM_SEMANTICANALYZER_H
#pragma once

#include <string>
#include <queue>
#include <map>
#include <vector>
#include <regex>

#include "Token.h"
#include "Errors.h"

using namespace std;

class SemanticAnalyzer {
private:
    vector<string> allBranches;
    uint8_t sectionType = 1; // section type defaults to 1 when not specified.

    void getSectionType(const string&);
    bool isExpressionInRightSection(const Tokens&) const;
    bool isDuplicateLabelName(const string&);
public:
    SemanticAnalyzer();
    void analyze(const pair<string, queue<Tokens>>&);
};


#endif //MIPSIM_SEMANTICANALYZER_H

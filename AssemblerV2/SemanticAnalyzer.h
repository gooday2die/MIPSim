//
// @file : SemanticAnalyzer.
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : 
// @date: 2022-03-17

#ifndef MIPSIM_SEMANTICANALYZER_H
#define MIPSIM_SEMANTICANALYZER_H
#pragma once

#include <string>
#include <queue>
#include <map>
#include <vector>

#include "Token.h"

using namespace std;

class SemanticAnalyzer {
private:
    vector<string> allBranches;

public:
    SemanticAnalyzer();
    void analyze(const pair<string, queue<Tokens>>&);
};


#endif //MIPSIM_SEMANTICANALYZER_H

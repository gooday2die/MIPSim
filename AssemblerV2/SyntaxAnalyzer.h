//
// @file : SyntaxAnalyzer.h
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : A file that defines all attributes and member functions for class SyntaxAnalyzer
// @date: 2022-03-17

#ifndef MIPSIM_SYNTAXANALYZER_H
#define MIPSIM_SYNTAXANALYZER_H
#pragma once

#include <map>
#include <string>
#include <queue>

#include "Token.h"
#include "Errors.h"

using namespace std;

/**
 * A class for analyzing syntax
 */
class SyntaxAnalyzer {
private:
    map<string, queue<Tokens>> allSyntax;
    static queue<Tokens> generateTokenQueue(const initializer_list<int> &il);
public:
    SyntaxAnalyzer();
    void analyze(const pair<string, queue<Tokens>>&);
};


#endif //MIPSIM_SYNTAXANALYZER_H

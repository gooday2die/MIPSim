//
// @file : Assembler.h
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : A file that defines all attributes and member functions for class Assembler
//

#ifndef MIPSIM_ASSEMBLER_H
#define MIPSIM_ASSEMBLER_H
#pragma once

#include <string>
#include <utility>
#include <vector>

#include "FileReader.h"
#include "Messages.h"
#include "LexicalAnalyzer.h"
#include "SyntaxAnalyzer.h"
#include "SemanticAnalyzer.h"
#include "Translator.h"
#include "../Simulator/Simulator.h"

using namespace std;

class Assembler {
private:
    string fileName;
    map<uint32_t, string> allExpressionStrings;
    map<uint32_t, pair<string, queue<Tokens>>> allTokens;

    uint32_t totalExpressionCount = 0;
    uint32_t totalLabelCount = 0;

    uint32_t* allMachineCodes = nullptr;

    FileReader* fileReader = nullptr;
    LexicalAnalyzer* lexicalAnalyzer = nullptr;
    SyntaxAnalyzer* syntaxAnalyzer = nullptr;
    SemanticAnalyzer* semanticAnalyzer = nullptr;
    Translator* translator = nullptr;
    Simulator* simulator = nullptr;

    uint32_t totalErrorCount = 0 ;

    void checkExpressionGrammar(const string&);
    void checkGrammar();

    void translate();
    void assemble();
    void simulate();
public:
    explicit Assembler(string);
};


#endif //MIPSIM_ASSEMBLER_H

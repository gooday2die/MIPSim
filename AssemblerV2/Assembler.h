//
// @file : Assembler.
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : 
// @date: 2022-03-15

#ifndef MIPSIM_ASSEMBLER_H
#define MIPSIM_ASSEMBLER_H
#pragma once

#include <string>
#include <utility>
#include <vector>

#include "FileReader.h"
#include "Section.h"
#include "Messages.h"
#include "LexicalAnalyzer.h"
#include "SyntaxAnalyzer.h"

using namespace std;

class Assembler {
private:
    string fileName;
    map<uint32_t, Expression> allExpressions;
    map<uint32_t, pair<string, queue<Tokens>>> allTokens;

    FileReader* fileReader = nullptr;
    Section* textSection = nullptr;
    Section* dataSection = nullptr;
    LexicalAnalyzer* lexicalAnalyzer = nullptr;
    SyntaxAnalyzer* syntaxAnalyzer = nullptr;

    uint32_t totalErrorCount = 0 ;

    uint16_t scanSections();
    void parseSections();

    void performLexicalAnalysis();
    void performSyntaxAnalysis();
public:
    explicit Assembler(string);
    void assemble();
};


#endif //MIPSIM_ASSEMBLER_H

//
// @file : Assembler.h
// @author : Gooday2die (Isu Kim)
// @Contacts : edina00@naver.com
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

#include "../Utils/defines.h"
#include "../Utils/Expression.h"

using namespace std;

/**
 * A class that is for implementing and declaring member functions of assembler.
 */
class Assembler {
private:
    string fileName;
    map<uint32_t, string> allExpressionStrings;

    uint32_t totalExpressionCount = 0;
    uint32_t totalLabelCount = 0;

    vector<Expression> textSectionExpressions;

    FileReader* fileReader = nullptr;
    LexicalAnalyzer* lexicalAnalyzer = nullptr;
    SyntaxAnalyzer* syntaxAnalyzer = nullptr;
    SemanticAnalyzer* semanticAnalyzer = nullptr;
    Translator* translator = nullptr;

    uint32_t totalErrorCount = 0 ;

    uint32_t* registers;
    uint32_t* pc;

    void checkExpressionGrammar(const string&);
    void checkGrammar();
    void translate();
    void assemble();
public:
    explicit Assembler(string, uint32_t*, uint32_t*);
    vector<Expression> getTextSectionExpressions();
};


#endif //MIPSIM_ASSEMBLER_H

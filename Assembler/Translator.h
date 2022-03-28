//
// @file : Translator.h
// @author : Gooday2die (Isu Kim)
// @Contacts : edina00@naver.com
// @brief : A file that defines all attributes and member functions for class Translator
//

#ifndef MIPSIM_TRANSLATOR_H
#define MIPSIM_TRANSLATOR_H
#pragma once

#include <string>
#include <queue>
#include <vector>
#include <map>
#include <regex>
#include <iostream>

#include "Token.h"
#include "Errors.h"
#include "../Utils/Expression.h"

using namespace std;


class Translator {
private:
    map<string, uint32_t> labelAddresses;
    map<string, uint32_t> registerMnemonics;
    map<string, uint32_t> instructionMnemonics;
    map<string, uint32_t> dataSectionLabel;
    map<string, uint32_t> textSectionLabel;

    uint32_t** registers;
    uint32_t* pc;

    /// Pseudo instructions are going to be translated into normal instructions.
    /// The map pseudoInstructionExpressionCounts represent how many normal instructions that current pseudo instruction
    /// will be turned into. This is for branch addressing and indexes.
    map<string, uint8_t> pseudoInstructionExpressionCounts;

    uint8_t currentSectionType = 1; // 1 text, 2 data. Defaults to text

    uint32_t dataSectionExpressionCount = 0;
    uint32_t textSectionExpressionCount = 0;

    uint32_t curTextSectionExpressionIndex = 0;

    uint8_t translateRegister(const string&);
    static uint16_t translateImmediate(const string&);
    pair<uint32_t, uint32_t> translateLabel(const string&, const string&);

    Expression translateExpression(const queue<Tokens>&, const string&);
    Expression generateExpressionObject(const vector<uint32_t*>&, const string&, uint32_t, const string&);
public:
    Translator(uint32_t**, uint32_t*);
    void scanLabelAddresses(const Tokens&, const string&);
    vector<Expression> translate(const queue<Tokens>&, const string&);
    void printLabels();
    uint16_t getLabelCount();
};


#endif //MIPSIM_TRANSLATOR_H

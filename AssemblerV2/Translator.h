//
// @file : Translator.h
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
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

#include "Token.h"
#include "Errors.h"

using namespace std;

enum Mnemonic{

};

class Translator {
private:
    map<string, uint32_t> labelAddresses;
    map<string, uint32_t> registerMnemonics;
    map<string, uint32_t> instructionMnemonics;

    uint8_t currentSectionType = 0; // 1 text, 2 data

    uint32_t dataSectionExpressionCount = 0;
    uint32_t textSectionExpressionCount = 0;

    uint8_t translateRegister(const string&);
    static uint16_t translateImmediate(const string&);
    uint16_t translateLabel(const string&);
public:
    Translator();
    void scanLabelAddresses(const Tokens&, const string&);
    uint32_t translate(const queue<Tokens>&, const string&);
};


#endif //MIPSIM_TRANSLATOR_H

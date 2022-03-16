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
#include "AssemblerError.h"

using namespace std;

class Assembler {
private:
    string fileName;
    map<uint32_t, Expression> allExpressions;
    vector<AssemblerError> allErrors;

    FileReader* fileReader = nullptr;
    Section* textSection = nullptr;
    Section* dataSection = nullptr;

    uint16_t scanSections();
    void parseSections();

public:
    explicit Assembler(string);
    void printErrors();
};


#endif //MIPSIM_ASSEMBLER_H

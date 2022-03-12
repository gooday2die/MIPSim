//
// @file : Assembler.h
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : A file that defines all attributes and member functions for class Assembler
// @date: 2022-03-10

#ifndef MIPSIM_ASSEMBLER_H
#define MIPSIM_ASSEMBLER_H
#pragma once

#include "FileReader.h"
#include "Translator.h"
#include "../Simulator/Simulator.h"
#include "Expression.h"
#include "Messages.h"
#include "GrammarChecker.h"

#include <tuple>


class Assembler {
private:
    std::map<uint32_t, std::string> allExpressions;
    std::map<std::string, uint32_t> allBranches;
    std::map<std::string, uint8_t> registerNames;
    std::map<uint32_t , std::string> processedExpressions;
    uint32_t* allMachineCodes;
    uint32_t totalErrorCount = 0;
    uint32_t totalLineCount = 0;

    std::string replaceRegisterName(const std::string&);
    void setRegisterNames();
    void checkGrammar();
public:
    Assembler(const char*);
    void translateAll();
    std::string replaceBranches(std::string);
    static bool replaceString(std::string&, const std::string&, const std::string&);
    uint32_t translateLine(std::string);
    void assemble();
};


#endif //MIPSIM_ASSEMBLER_H

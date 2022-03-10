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

class Assembler {
private:
    std::map<uint32_t, std::string> allExpressions;
    std::map<std::string, uint32_t> allBranches;
    uint32_t* allMachineCodes;
public:
    Assembler(const char*);
    void translateAll();
    std::string replaceBranches(std::string);
    static bool replaceString(std::string&, const std::string&, const std::string&);
    uint32_t translateLine(std::string);
};


#endif //MIPSIM_ASSEMBLER_H

//
// @file : GrammarChecker.h
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : A file that defines all attributes and member functions for class GrammarChecker
// @date: 2022-03-12

#ifndef MIPSIM_GRAMMARCHECKER_H
#define MIPSIM_GRAMMARCHECKER_H
#pragma once

#include <string>
#include <map>
#include <algorithm>
#include <vector>
#include <stdexcept>
#include <iostream>
#include "AssemblerErrors.h"


class GrammarChecker {
private:
    static bool isDuplicateBranchName(const std::string&, const std::map<std::string, uint32_t>&);
    static uint8_t getInstructionType(const std::string&);
    static void checkArgumentsValidity(const std::string&);
public:
    static void checkBranchName(const std::string&, std::map<std::string, uint32_t>);
    static void checkExpressionValidity(std::string, std::map<std::string, uint32_t>);
};


#endif //MIPSIM_GRAMMARCHECKER_H

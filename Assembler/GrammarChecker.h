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


typedef struct argumentInfo{
    uint8_t total;
    uint8_t registers;
    uint8_t immediates;
    uint8_t addresses;
}argumentInfo;

/**
 * A enumeration for arguments
 * 0b00000000
 * MSB 2 bits : for total number of arguments
 * Next 2 bits : for total number of register arguments
 * Next 2 bits : for total number of immediate arguments
 * LSB 2 bit : for total number of address arguments.
 * ex) 0b1111000 -> total of 3 arguments with 3 register arguments
 */
enum InstructionArgInfo{
   Aadd  = 0b1111000, // R Type
   Aaddu = 0b1111000,
   Aand = 0b1111000,
   Anor = 0b1111000,
   Aor = 0b1111000,
   Aslt = 0b1111000,
   Asltu = 0b1111000,
   Asub = 0b1111000,
   Asubu = 0b1111000,
   Ajr = 0b01010000, // Needs one register argument

   Aaddi = 0b11100100, // I type
   Aaddiu = 0b11100100,
   Aandi = 0b11100100,
   Aori = 0b11100100,
   Aslti = 0b11100100,
   Asltiu = 0b11100100,
   Abeq = 0b11100001,
   Abne = 0b11100001,

   Asll = 0b11100100, // Needs two registers and one immediate
   Asrl = 0b11100100,

   Aj = 0b01000001, // Needs one address
   Ajal = 0b01000001, // Needs one address

   Amove = 0b10100000, // two registers
   Ali = 0b10010100, // one register, one immediate
   //A_lw = 0b00000000,
   //A_la = 0b00000000,
   Ablt = 0b11100001, // two registers, one address
   Able = 0b11100001,
   Abgt = 0b11100001,
   Abge = 0b11100001,
};

class GrammarChecker {
private:
    std::map<std::string, uint32_t>* allBranches;
    std::map<std::string, uint32_t> branchDeclarationCount;
    bool isBranchName(const std::string&);
    static bool isValidRegister(const std::string&);
    static bool isValidImmediate(const std::string&);
    bool isValidAddress(const std::string&);
    bool isValidBranchAddress(const std::string&);

    static uint8_t getInstructionType(const std::string&);
    void checkArgumentsValidity(const std::string&);
    static argumentInfo getArgumentInfo(const std::string&);
    static argumentInfo getExpressionArguments(const std::string&);
public:
    GrammarChecker(std::map<std::string, uint32_t>*);
    void checkBranchName(const std::string&);
    void checkExpressionValidity(const std::string&);
};


#endif //MIPSIM_GRAMMARCHECKER_H

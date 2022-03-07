//
// @file : MachineCode.h
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : A code that defines all attributes and member function for class MachineCode
// @date: 2022-03-07

#ifndef MIPSIM_MACHINECODE_H
#define MIPSIM_MACHINECODE_H
#pragma once

#include <cstdint>


/**
 * A class for MachineCode
 * CodeType is defined as following:
 * 1 = R Type Instruction
 * 2 = I Type Instruction
 * 3 = J Type Instruction
 */
class MachineCode {
private:
    int code;
    uint8_t codeType;

public:
    MachineCode(int, uint8_t);
    int getcode();
    uint8_t getCodeType();
};


#endif //MIPSIM_MACHINECODE_H

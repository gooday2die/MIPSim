//
// @file : Instructions.h
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : A file that defines every attribute and member function for class Instructions
// @date: 2022-03-07

#ifndef MIPSIM_INSTRUCTIONS_H
#define MIPSIM_INSTRUCTIONS_H
#pragma once

#include <stdexcept>
#include <cstdint>
#include <climits>
#include "../Register/Register.h"

class Instructions {
public:
    class RType{
    public:
        static void _add(Register*, Register*, Register*);
        static void _addu(Register*, Register*, Register*);
        static void _and(Register*, Register*, Register*);
        static void _nor(Register*, Register*, Register*);
        static void _or(Register*, Register*, Register*);
        static void _slt(Register*, Register*, Register*);
        static void _sltu(Register*, Register*, Register*);
    };
    class IType{
    public:
        static void _addi(Register*, Register*, uint16_t);
        static void _addiu(Register*, Register*, uint16_t);
        static void _andi(Register*, Register*, uint16_t);
        static void _ori(Register*, Register*, uint16_t);
        static void _slti(Register*, Register*, uint16_t);
        static void _sltiu(Register*, Register*, uint16_t);
    };
    class JType{
    public:
    };
};


#endif //MIPSIM_INSTRUCTIONS_H

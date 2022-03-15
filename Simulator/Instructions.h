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
#include <iostream>


class Instructions {
public:
    class RType{
    public:
        static void _add(uint32_t, uint32_t, uint32_t*);
        static void _addu(uint32_t, uint32_t, uint32_t*);
        static void _and(uint32_t, uint32_t, uint32_t*);
        static void _nor(uint32_t, uint32_t, uint32_t*);
        static void _or(uint32_t, uint32_t, uint32_t*);
        static void _slt(uint32_t, uint32_t, uint32_t*);
        static void _sltu(uint32_t, uint32_t, uint32_t*);
        static void _sub(uint32_t, uint32_t, uint32_t*);
        static void _subu(uint32_t, uint32_t, uint32_t*);
        static void _jr(uint32_t*, uint32_t);
        static void _sll(uint32_t, uint32_t*, uint8_t);
        static void _srl(uint32_t, uint32_t*, uint8_t);

    };
    class IType{
    public:
        static void _addi(uint32_t, uint32_t*, uint16_t);
        static void _addiu(uint32_t, uint32_t*, uint16_t);
        static void _andi(uint32_t, uint32_t*, uint16_t);
        static void _ori(uint32_t, uint32_t*, uint16_t);
        static void _slti(uint32_t, uint32_t*, uint16_t);
        static void _sltiu(uint32_t, uint32_t*, uint16_t);
        static void _beq(uint32_t, uint32_t, uint32_t, uint32_t*);
        static void _bne(uint32_t, uint32_t, uint32_t, uint32_t*);
    };
    class JType{
    public:
        static void _j(uint32_t*, uint32_t);
        static void _jal(uint32_t*, uint32_t*, uint32_t);
    };
};


#endif //MIPSIM_INSTRUCTIONS_H

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
#include "AbstractInstructions.h"


class Instructions {
public:
    class _add : public RType{
        static void execute(Register, Register, Register);
    };
};


#endif //MIPSIM_INSTRUCTIONS_H

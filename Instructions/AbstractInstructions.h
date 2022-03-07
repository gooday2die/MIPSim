//
// @file : AbstractInstructions.h
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : A header file that contains all instruction abstraction classes
// @date: 2022-03-07

#ifndef MIPSIM_ABSTRACTINSTRUCTIONS_H
#define MIPSIM_ABSTRACTINSTRUCTIONS_H

#pragma once

#include <cstdint>
#include "../Register/Register.h"


/**
 * An abstract class for all instructions with MIPS assembly
 */
class AbstractInstructions {
    virtual void execute(){} // the member function that should be overridden with each type
};

/**
 * An abstract class for I Type instructions. This inherits from class AbstractInstructions
 */
class RType : public AbstractInstructions{
    void execute(Register, Register, Register){};
};

/**
 * An abstract class for I Type instructions. This inherits from class AbstractInstructions
 */
class IType : public AbstractInstructions{
    void execute(Register, Register, uint16_t){};
};

/**
 * An abstract class for J Type instructions. This inherits from class AbstractInstructions
 */
class JType : public AbstractInstructions{
    void execute(Register, uint32_t){};
};


#endif //MIPSIM_ABSTRACTINSTRUCTIONS_H

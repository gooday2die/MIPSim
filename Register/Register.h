//
// @file : Register.h
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : A file that defines all attributes and member functions for class Register
// @date: 2022-03-07

#ifndef MIPSIM_REGISTER_H
#define MIPSIM_REGISTER_H
#pragma once

#include <cstdint>


/**
 * A class for a single register
 */
class Register {
private:
    uint32_t value; // the 32 bit value stored in a register
public:
    Register(uint32_t);
    uint32_t getValue();
    void setValue(uint32_t);
};


#endif //MIPSIM_REGISTER_H

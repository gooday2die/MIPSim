//
// @file : Register.h
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : A file that defines all attributes and member functions for class Register
// @date: 2022-03-07

#ifndef MIPSIM_REGISTER_H
#define MIPSIM_REGISTER_H
#pragma once


/**
 * A class for a single register
 */
class Register {
private:
    int value; // the 32 bit value stored in a register
public:
    Register(int);
    int getValue();
    void setValue(int);
};


#endif //MIPSIM_REGISTER_H

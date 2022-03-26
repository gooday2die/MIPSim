//
// @file : RegisterHandler.h
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : A file that defines all attributes and member functions for class RegisterHandler
//

#ifndef MIPSIM_REGISTERHANDLER_H
#define MIPSIM_REGISTERHANDLER_H
#pragma once

#include <cstdlib>
#include <cstdint>
#include <cstdio>


enum RegisterNames{
     zero = 0,
     at = 1,
     v0 = 2,
     v1 = 3,
     a0 = 4,
     a1 = 5,
     a2 = 6,
     a3 = 7,
     t0 = 8,
     t1 = 9,
     t2 = 10,
     t3 = 11,
     t4 = 12,
     t5 = 13,
     t6 = 14,
     t7 = 15,
     s0 = 16,
     s1 = 17,
     s2 = 18,
     s3 = 19,
     s4 = 20,
     s5 = 21,
     s6 = 22,
     s7 = 23,
     t8 = 24,
     t9 = 25,
     k0 = 26,
     k1 = 27,
     gp = 28,
     sp = 29,
     fp = 30,
     ra = 31
};

/**
 * A class for handling registers including PC
 */
class RegisterHandler {
private:
    uint32_t* registers;
    uint32_t pc;
public:
    RegisterHandler();
    uint32_t* getRegister(int);
    uint32_t* getPC();
    uint32_t* getAllRegisters();
    void printAllRegisters();
    void resetZero();
};


#endif //MIPSIM_REGISTERHANDLER_H

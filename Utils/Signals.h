//
// @file : Signals.h
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : A file that defines all signals within simulator
//

#ifndef MIPSIM_SIGNALS_H
#define MIPSIM_SIGNALS_H
#pragma once

#include <exception>


class Syscall{
public:
    class Exit : public std::exception {
    };
};

class GeneralExceptions{
public:
    class OverflowException : public std::exception{
    };
    class UnknownInstruction : public std::exception{
    };
};

#endif //MIPSIM_SIGNALS_H

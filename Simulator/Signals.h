//
// @file : Signals.
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : 
// @date: 2022-03-26

#ifndef MIPSIM_SIGNALS_H
#define MIPSIM_SIGNALS_H
#pragma once

#include <exception>


class Syscall{
public:
    class Exit : public std::exception {
    };
};

#endif //MIPSIM_SIGNALS_H

//
// @file : main.h
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : a Header file for main.cpp
// @date: 2022-03-10

#ifndef MIPSIM_MAIN_H
#define MIPSIM_MAIN_H
#pragma once

#include "./Parser/Assembler.h"

#include <iostream>
#include <queue>
#include <cstring>


enum commands{
    help = 1,
    runFile = 2,
    dev = 3,
    unknown = 4
};
void argHandler(int argc, char** argv);
commands getCommandType(std::string);

#endif //MIPSIM_MAIN_H

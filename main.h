//
// @file : main.h
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : a Header file for main.cpp
//

#ifndef MIPSIM_MAIN_H
#define MIPSIM_MAIN_H
#pragma once

#include "./AssemblerV2/Assembler.h"
#include "./Simulator/Simulator.h"

#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

enum commands{
    help = 1,
    runFile = 2,
    dev = 3,
    unknown = 4,
    assembleFile = 5,
};
void argHandler(int argc, char** argv);
commands getCommandType(const string& argString);
map<string, uint32_t*> assemble(const string&);
void simulate(const map<string, uint32_t*>&);

#endif //MIPSIM_MAIN_H

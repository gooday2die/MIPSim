//
// @file : main.h
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : a Header file for main.cpp
// @date: 2022-03-10

#ifndef MIPSIM_MAIN_H
#define MIPSIM_MAIN_H
#pragma once

#include "Simulator/SimulatorTests.h"
#include "Parser/Assembler.h"
#include "Simulator/Simulator.h"
#include "Parser/FileReader.h"

#include <iostream>
#include <queue>


enum commands{
    help = 1,
    runFile = 2,
    dev = 3
};
void argHandler(int argc, char** argv);
commands getCommandType(std::string);

#endif //MIPSIM_MAIN_H

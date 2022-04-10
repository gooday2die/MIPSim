//
// @file : ArgumentHandler.h
// @author : Gooday2die (Isu Kim)
// @Contacts : edina00@naver.com
// @brief : A file that defines all attributes and member functions for class ArgumentHandler
// 

#ifndef MIPSIM2_ARGUMENTHANDLER_H
#define MIPSIM2_ARGUMENTHANDLER_H
#pragma once

#include <cstdint>
#include <string>
#include <iostream>

#include "Utils/defines.h"
#include "MIPSim.h"

using namespace std;

class ArgumentHandler {
private:
    int argc;
    char** argv;
public:
    ArgumentHandler(int, char**);
    static uint8_t getCommandType(const string&);
    void run();
};


#endif //MIPSIM2_ARGUMENTHANDLER_H

//
// @file : Simulator.h
// @author : Gooday2die (Isu Kim)
// @Contacts : edina00@naver.com
// @brief : 
// 

#ifndef MIPSIM2_SIMULATOR_H
#define MIPSIM2_SIMULATOR_H
#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "../Utils/Expression.h"
#include "../Utils/Signals.h"

using namespace std;

class Simulator {
private:
    vector<Expression> textSectionExpressions;
    uint32_t** registers = nullptr;
    uint32_t* pc;

public:
    Simulator(uint32_t**, uint32_t*, const vector<Expression>&);
    void run();
};


#endif //MIPSIM2_SIMULATOR_H

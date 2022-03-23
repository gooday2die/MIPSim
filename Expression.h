//
// @file : Expression.
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : 
//

#ifndef MIPSIM_EXPRESSION_H
#define MIPSIM_EXPRESSION_H
#pragma once

#include <cstdint>
#include <string>

using namespace std;

class Expression {
private:
    uint32_t address;
    string expressionString;
    string instructionString;
};


#endif //MIPSIM_EXPRESSION_H

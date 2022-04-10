//
// @file : Expression.h
// @author : Gooday2die (Isu Kim)
// @Contacts : edina00@naver.com
// @brief : A file that defines all attributes and member functions for class Expression
//

#ifndef MIPSIM2_EXPRESSION_H
#define MIPSIM2_EXPRESSION_H
#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "Instruction.h"

using namespace std;

class Expression {
private:
    string expressionString;
    Instruction* instruction;
    uint32_t machineCode;
public:
    Expression(const vector<uint32_t*>&, const string&, const string&, uint32_t);
    void execute();
    void print();
};


#endif //MIPSIM2_EXPRESSION_H

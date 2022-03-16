//
// @file : Expression.h
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : A file that defines all attributes and member functions for class Expression
// @date: 2022-03-15

#ifndef MIPSIM_EXPRESSION_H
#define MIPSIM_EXPRESSION_H
#pragma once

#include <string>
#include <algorithm>
#include <vector>

class Expression {
private:
    std::string expressionString;
    uint32_t expressionAddress;
public:
    Expression(std::string&);
    void setExpressionAddress(uint32_t);
    uint32_t getExpressionAddress();
    std::string getExpressionString() const;
    bool isLabelExpression();
    bool isEmptyExpression();
};


#endif //MIPSIM_EXPRESSION_H

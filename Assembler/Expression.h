//
// @file : Expression.h
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : A file that defines all attributes and member functions for class Expression
// @date: 2022-03-12

#ifndef MIPSIM_EXPRESSION_H
#define MIPSIM_EXPRESSION_H
#pragma once

#include <string>
#include <algorithm>

class Expression {
private:
    std::string expressionString;
    void removeComments();
    void removeTabs();
    void addWhiteSpace();
    void makeOneWhiteSpace();
public:
    Expression(std::string);
    bool isBranchExpression();
    std::string getBranchName();
    void preprocess();
    std::string getString() const;
};


#endif //MIPSIM_EXPRESSION_H

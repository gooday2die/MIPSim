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
#include <vector>

class Expression {
private:
    std::string expressionString;
    std::vector<std::string> translatedPseudoInstruction;
    void removeComments();
    void removeTabs();
    void addWhiteSpace();
    void makeOneWhiteSpace();
public:
    Expression(std::string);
    bool isBranchExpression();
    bool isPseudoInstruction();
    std::string getBranchName();
    void preprocess();
    std::string getString() const;
    std::vector<std::string> getTranslatedPseudoInstruction();
};


#endif //MIPSIM_EXPRESSION_H

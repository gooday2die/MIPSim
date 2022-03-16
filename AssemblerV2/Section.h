//
// @file : Section.
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : 
// @date: 2022-03-15

#ifndef MIPSIM_SECTION_H
#define MIPSIM_SECTION_H
#pragma once

#include <vector>
#include <iostream>
#include "Expression.h"
#include "Label.h"

class Section {
private:
    std::vector<Expression> allExpressions;
    std::vector<Label> allLabels;
    uint8_t type; // text section: 1, data section: 2
    uint32_t startingAddress;
    void scanLabels();
public:
    Section(std::vector<Expression>, uint8_t);
    void printSection();
    void checkGrammar();

};


#endif //MIPSIM_SECTION_H

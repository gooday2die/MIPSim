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
#include "Expression.h"

class Section {
private:
    std::vector<Expression> allExpressions;
    uint8_t type; // text section: 1, data section: 2
    uint32_t startingAddress;
public:
    Section(std::vector<Expression>, uint8_t);
};


#endif //MIPSIM_SECTION_H

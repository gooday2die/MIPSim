//
// @file : Section.
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : 
// @date: 2022-03-15

#include "Section.h"

#include <utility>

Section::Section(std::vector<Expression> sectionExpressions, uint8_t sectionType) {
    this->allExpressions = std::move(sectionExpressions);
    this->type = sectionType;
    if(this->type == 1) this->startingAddress = 0x00400000;
    else if(this->type == 2) this->startingAddress = 0x10000000;
}
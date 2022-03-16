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

void Section::printSection(){
    uint32_t i = 0;
    if(this->type == 1) std::cout << "TEXT Section" << std::endl;
    else if(this->type == 2) std::cout << "DATA Section" << std::endl;
    for(const Expression& x : this->allExpressions){
        std::cout << std::to_string(i) << " : " << x.getExpressionString() << std::endl;
        i++;
    }
}

void Section::scanLabels() {
    for(Expression x : this->allExpressions){
        if(x.isLabelExpression()){
            Label newLabel = Label(x.getExpressionString());
            this->allLabels.push_back(newLabel);
        }
    }
}

void Section::checkGrammar(){

}
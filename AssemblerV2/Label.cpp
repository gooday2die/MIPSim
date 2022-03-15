//
// @file : Label.
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : 
// @date: 2022-03-15

#include "Label.h"

Label::Label(const string& argName) {
    this->labelName = argName;
}

uint32_t Label::getAddress() {
    return this->address;
}

void Label::setAddress(uint32_t argAddress) {
    this->address = argAddress;
}

string Label::getLabelName() {
    return this->labelName;
}
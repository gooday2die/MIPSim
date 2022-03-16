//
// @file : Expression.cpp
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : A file that implements all member functions for class Expression
// @date: 2022-03-15

#include "Expression.h"

Expression::Expression(std::string& argExpressionString) {
    this->expressionString = argExpressionString;
}

void Expression::setExpressionAddress(uint32_t argAddress) {
    this->expressionAddress = argAddress;
}

uint32_t Expression::getExpressionAddress() {
    return this->expressionAddress;
}

std::string Expression::getExpressionString() const {
    return this->expressionString;
}
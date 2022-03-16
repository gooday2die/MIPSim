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

/**
 * A member function for class Expression to check if current expression is a declaration of branch
 * @return returns true if current expression was declaration of branch, false if not
 */
bool Expression::isLabelExpression() {
    const char* line = this->expressionString.c_str();
    uint16_t curPos = 0;
    while(line[curPos] != '\0'){
        if(line[curPos] == ':') return true;
        else curPos++;
    }
    return false;
}

bool Expression::isEmptyExpression() {
    return this->expressionString.empty();
}
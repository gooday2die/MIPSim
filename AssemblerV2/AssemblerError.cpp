//
// @file : AssemblerError.
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : 
// @date: 2022-03-15

#include "AssemblerError.h"

AssemblerError::AssemblerError(const string& argErrorReason, const string& argErrorExpression, uint32_t argErrorLine) {
    this->errorReason = argErrorReason;
    this->errorExpression = argErrorExpression;
    this->errorLine = argErrorLine;
}

void AssemblerError::print() {
    std::cout << ERROR_TAG << " " << this->errorReason << " ";
    std::cout << "@ln " << this->errorLine << " -> " << ERROR_EXPRESSION << std::endl;
}
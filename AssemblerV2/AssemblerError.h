//
// @file : AssemblerError.
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : 
// @date: 2022-03-15

#ifndef MIPSIM_ASSEMBLERERROR_H
#define MIPSIM_ASSEMBLERERROR_H
#pragma once

#ifdef _WIN32
#define ERROR_TAG "[ERROR]"
#define ASSEMBLE_FAILED "Failed to assemble"
#define ASSEMBLE_SUCCESS "Successfully assembled"
#define ERROR_EXPRESSION this->errorExpression
#endif


// Linux deserves color output. :)
#ifdef linux
#define ERROR_TAG "\x1B[31m[ERROR]\033[0m"
#define ASSEMBLE_FAILED "\x1B[31mFailed to assemble\033[0m"
#define ASSEMBLE_SUCCESS "\x1B[32mSuccessfully assembled\033[0m"
#define ERROR_EXPRESSION "\x1B[93m" << this->errorExpression << "\033[0m"
#endif

#include <iostream>
#include <string>

using namespace std;

class AssemblerError {
public:
    AssemblerError(const string&, const string&, uint32_t);
    string errorReason;
    string errorExpression;
    uint32_t errorLine;
    void print();
};


#endif //MIPSIM_ASSEMBLERERROR_H

//
// @file : FileReader.h
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : A file that defines all attributes and member functions for class FileReader
// @date: 2022-03-10

#ifndef MIPSIM_FILEREADER_H
#define MIPSIM_FILEREADER_H
#pragma once

// Windows don't deserve color output. :b
#ifdef _WIN32
#define ERROR_TAG "[ERROR]"
#define ASSEMBLE_FAILED "Failed to assemble"
#define ASSEMBLE_SUCCESS "Successfully assembled"
#define ERROR_EXPRESSION curLine
#endif


// Linux deserves color output. :)
#ifdef linux
#define ERROR_TAG "\x1B[31m[ERROR]\033[0m"
#define ASSEMBLE_FAILED "\x1B[31mFailed to assemble\033[0m"
#define ASSEMBLE_SUCCESS "\x1B[32mSuccessfully assembled\033[0m"
#define ERROR_EXPRESSION "\x1B[93m" << curLine << "\033[0m"
#endif

#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <map>

#include "Expression.h"

class FileReader {
private:
    std::map<uint32_t, std::string> allExpressions;
    std::map<std::string, uint32_t> allBranches;
    bool isDuplicateBranchName(std::string);
public:
    FileReader(const char*);
    static std::string getBranch(std::string);
    std::map<std::string, uint32_t> getAllBranches();
    std::map<uint32_t, std::string> getAllExpressions();
    static std::string getCurrentDirectory(std::string);
};


#endif //MIPSIM_FILEREADER_H

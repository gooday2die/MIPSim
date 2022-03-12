//
// @file : FileReader.h
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : A file that defines all attributes and member functions for class FileReader
// @date: 2022-03-10

#ifndef MIPSIM_FILEREADER_H
#define MIPSIM_FILEREADER_H
#pragma once

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

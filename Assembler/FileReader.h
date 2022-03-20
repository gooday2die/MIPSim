//
// @file : FileReader.h
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : A file that defines all attributes and member functions for class FileReader
//

#ifndef MIPSIM_FILEREADER_H
#define MIPSIM_FILEREADER_H
#pragma once

#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <map>
#include <regex>
#include <tuple>

#include "Expression.h"
#include "Messages.h"
#include "AssemblerErrors.h"

class FileReader {
private:
    std::map<uint32_t, std::string> allExpressions;
    std::ifstream fileObject;
public:
    FileReader(const char*);
    std::map<uint32_t, std::string> getAllExpressions();
    static std::string getCurrentDirectory(std::string);
};


#endif //MIPSIM_FILEREADER_H

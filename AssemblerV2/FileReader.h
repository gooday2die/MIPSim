//
// @file : FileReader.h
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : A file that defines all attributes and member functions for class FileReader
// @date: 2022-03-15

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

using namespace std;

/**
 * A class for reading, preprocessing and generating expressions
 */
class FileReader {
private:
    map<uint32_t, Expression> allExpressions;
    ifstream fileObject;
    static string getCurrentDirectory(const string&);
    static string preProcess(const string&);
    static string removeTabs(const string&);
    static string removeComments(const string&);
    static string removeDuplicateWhitespaces(const string&);
public:
    explicit FileReader(const string&);
    map<uint32_t, Expression> getAllExpressions();
};


#endif //MIPSIM_FILEREADER_H

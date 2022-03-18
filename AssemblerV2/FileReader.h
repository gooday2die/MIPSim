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
#include <algorithm>

using namespace std;


/**
 * A class for reading, preprocessing and generating expressions
 */
class FileReader {
private:
    map<uint32_t, string> allExpressions;
    ifstream fileObject;
    static string getCurrentDirectory(const string&);
    static string preProcess(const string&);
    static string removeTabs(const string&);
    static string removeComments(const string&);
    static string removeDuplicateWhitespaces(const string&);
    static string addWhiteSpace(const string&);
    static string replaceTabToWhitespaces(const string&);
    static string removeCommas(const string&);
public:
    explicit FileReader(const string&);
    map<uint32_t, string> getAllExpressions();
};


#endif //MIPSIM_FILEREADER_H

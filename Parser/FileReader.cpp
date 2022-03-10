//
// @file : FileReader.cpp
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : A file that implements all member functions for class FileReader
// @date: 2022-03-10

#include "FileReader.h"


/**
 * A constructor member function for FileReader
 * This stores all expressions as string object in a queue
 * @param fileName the file directory to load file.
 */
FileReader::FileReader(const char* fileName) {
    std::ifstream fileObject = std::ifstream(fileName);
    if (!fileObject){
        std::cout << "Error: Cannot locate file: " << fileName << std::endl;
        exit(1);
    }else{
        while(!fileObject.eof()){
            std::string curLine;
            std::getline(fileObject, curLine, '\n');
            curLine = removeComments(curLine);
            curLine = removeTabs(curLine);
            std::cout << curLine << std::endl;
            this->allExpressions.push(curLine);
        }
    }
}

/**
 * A member function for FileReader that removes comments from codes
 * @param curLine the current line to check if there are comments
 * @return returns string object that contains code without comments.
 */
std::string FileReader::removeComments(std::string curLine) {
    char* line = (char*)curLine.c_str();
    uint16_t curPos = 0;
    while(line[curPos] != '\0'){
        if(line[curPos] == '#'){
            line[curPos] = '\0';
            break;
        }
        curPos++;
    }
    return line;
}

/**
 * A member function for class FileReader that removes all tabs and whitespaces before code starts
 * @param curLine the string object of code for current line
 * @return returns string object that just has code without tabs and whitespaces before code
 */
std::string FileReader::removeTabs(std::string curLine) {
    return removeTabsTabs(removeTabsSpaces(curLine));
}

/**
 * A member function that removes whitespaces before real code starts
 * @param curLine the current line to check if there are any spaces.
 * @return returns string object that contains code without whitespaces before code
 */
std::string FileReader::removeTabsSpaces(std::string curLine) {
    const char* line = curLine.c_str();
    uint16_t curPos = 0;
    while (line[curPos] == 32) curPos++;
    return curLine.substr(curPos, curLine.size());
}

/**
 * A member function that removes spaces before real code starts
 * @param curLine the current line to check if there are any spaces.
 * @return returns string object that contains code without tabs before code
 */
std::string FileReader::removeTabsTabs(std::string curLine) {
    const char* line = curLine.c_str();
    uint16_t curPos = 0;
    while (line[curPos] == 9) curPos++;
    return curLine.substr(curPos, curLine.size());
}
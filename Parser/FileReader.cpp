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
            this->allExpressions.push(curLine);
        }
    }
    while(! this->allExpressions.empty()){
        std::cout<< this->allExpressions.front() << std::endl;
        this->allExpressions.pop();
    }
}
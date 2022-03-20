//
// @file : FileReader.cpp
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : A file that implements all member functions for class FileReader
//

#include <algorithm>
#include "FileReader.h"


/**
 * A constructor member function for FileReader
 * This stores all expressions as string object in a queue, as well as making a map for branches
 * @param fileName the file directory to load file.
 */
FileReader::FileReader(const char* fileName) {
    this->fileObject = std::ifstream(fileName); // try loading it with absolute path
    uint32_t expressionCount = 0;
    if (!fileObject) { // if we could not load it, try relative path
        std::ifstream fileObject = std::ifstream(FileReader::getCurrentDirectory(fileName) + "/" + fileName);
        if (!fileObject) { // if relative path failed, just exit
            std::cout << "Error: Cannot locate file: " << fileName << std::endl;
            exit(1);
        }
    }
    uint32_t totalLineCount = 0;

    while (!fileObject.eof()) {
        std::string curLine;
        std::getline(fileObject, curLine, '\n');
        this->allExpressions.insert(std::pair<uint32_t, std::string>(totalLineCount, curLine));
        totalLineCount++;
    }
}

/**
 * A getter member function for attribute allExpressions
 * @return returns allExpressioins in map object
 */
std::map<uint32_t, std::string> FileReader::getAllExpressions() {
    return this->allExpressions;
}

/**
 * A member function for class FileReader that retrieves current working directory
 * This looks for the last / or \ that separates directories and return all the string before / or \ as working directory.
 * @param curFile the current executable file in full directory
 * @return current working directory
 */
std::string FileReader::getCurrentDirectory(std::string curFile){
    for(uint32_t curPos = curFile.size() ; curPos >= 0 ; curPos--){
        if ((curFile.c_str()[curPos] == '/') || (curFile.c_str()[curPos] == '\\')){
            return curFile.substr(0, curPos);
        }
    }
    return "";
}

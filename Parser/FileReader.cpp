//
// @file : FileReader.cpp
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : A file that implements all member functions for class FileReader
// @date: 2022-03-10

#include <algorithm>
#include "FileReader.h"


/**
 * A constructor member function for FileReader
 * This stores all expressions as string object in a queue, as well as making a map for branches
 * @param fileName the file directory to load file.
 */
FileReader::FileReader(const char* fileName) {
    std::ifstream fileObject = std::ifstream(fileName); // try loading it with absolute path
    uint32_t curLineCount = 0;
    if (!fileObject){ // if we could not load it, try relative path
        std::ifstream fileObject = std::ifstream(FileReader::getCurrentDirectory(fileName) + "/" + fileName);
        if (!fileObject) { // if relative path failed, just exit
            std::cout << "Error: Cannot locate file: " << fileName << std::endl;
            exit(1);
        }
    }
    while(!fileObject.eof()){
        std::string curLine;
        std::getline(fileObject, curLine, '\n');
        if (!curLine.empty()) { // remove unnecessary new lines
            curLine = removeComments(curLine); // remove comments from code
            curLine = removeTabs(curLine); // remove tabs before code
            std::string curBranchName = FileReader::getBranch(curLine); // get branch name
            if (!curBranchName.empty()) {  // if current line is a declaration of branch, add it to the map
                this->allBranches.insert(std::pair<std::string, int>(curBranchName, curLineCount));
            } else{ // if this was not a branch declaration, just add it to the allExpressions map
                curLine = addWhiteSpace(curLine); // add whitespace to the last character
                curLine = makeOneWhiteSpace(curLine); // remove two or more consecutive whitespaces
                this->allExpressions.insert(std::pair<uint32_t, std::string>(curLineCount, curLine));
                curLineCount++;
            }
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

/**
 * A member function that gets all branch's names
 * @param curLine the current line to check if there is a branch
 * @return returns string object that contains current branch's name. Empty string if there is no branch in this line.
 */
std::string FileReader::getBranch(std::string curLine) {
    const char* line = curLine.c_str();
    uint16_t curPos = 0;
    while(line[curPos] != '\0'){
        if(line[curPos] == ':') return curLine.substr(0, curPos);
        else curPos++;
    }
    return "";
}

/**
 * A getter member function for attribute allBranches
 * @return returns allBranches in map object
 */
std::map<std::string, uint32_t> FileReader::getAllBranches() {
    return this->allBranches;
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

/**
 * A member function that inserts a whitespace to end of expression
 * @param curLine the current line to look for
 * @return returns expression with whitespace
 */
std::string FileReader::addWhiteSpace(std::string curLine) {
    const char* line = curLine.c_str();
    if (line[curLine.size() - 1] != 32){ // string's size just returns \0's index. So this is total len - 1
        // check if last character was a space, if it was not add one
        char* result = (char*)malloc(sizeof(char) * (curLine.size() + 1)); // copy all
        for (uint32_t i = 0; i < curLine.size() ; i++) result[i] = line[i];
        result[curLine.size()] = 32; // add space
        result[curLine.size() + 1] = '\0'; // add a \0
        std::string returnString = std::string(result);
        return returnString; // return edited
    }
    return curLine; // return original
}

/**
 * A member function that makes two or more consecutive whitespaces into one whitespace
 * Main idea came from https://stackoverflow.com/questions/8362094/replace-multiple-spaces-with-one-space-in-a-string
 * @param curLine the current line to look for
 * @return returns expression with one whitespaces without to or more consecutive whitespaces
 */
std::string FileReader::makeOneWhiteSpace(std::string curLine) {
    std::string::iterator new_end = std::unique(curLine.begin(), curLine.end(), [](char lhs, char rhs) { return (lhs == rhs) && (lhs == ' '); });
    curLine.erase(new_end, curLine.end());
    return curLine;
}
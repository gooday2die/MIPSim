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
    uint32_t expressionCount = 0;
    uint32_t errorCount = 0;
    if (!fileObject){ // if we could not load it, try relative path
        std::ifstream fileObject = std::ifstream(FileReader::getCurrentDirectory(fileName) + "/" + fileName);
        if (!fileObject) { // if relative path failed, just exit
            std::cout << "Error: Cannot locate file: " << fileName << std::endl;
            exit(1);
        }
    }

    uint32_t totalLineCount = 0;
    std::cout << "Assembling... " << std::endl;
    while(!fileObject.eof()){
        std::string curLine;
        std::getline(fileObject, curLine, '\n');
        Expression expression = Expression(curLine);
        totalLineCount++;

        if(expression.isBranchExpression()) { // if current expression is branch expression
            std::string branchName = expression.getBranchName();
            if (isDuplicateBranchName(branchName)) { // if this branch name was defined earlier
                std::cout << "Found duplicate branch name ";
                if(OS)
                    std::cout << "@ln " << totalLineCount << " -> " << curLine << std::endl;
                else
                    std::cout << "@ln " << totalLineCount << " -> " << "\x1B[31m" << curLine << "\033[0m" << std::endl;
                errorCount++;
                exit(1);
            }
            else if(branchName.empty()){ // if the branch name was empty. Ex) :
                std::cout << "Branch name cannot be empty " ;
                if(OS)
                    std::cout << "@ln " << totalLineCount << " -> " << curLine << std::endl;
                else
                    std::cout << "@ln " << totalLineCount << " -> " << "\x1B[31m" << curLine << "\033[0m" << std::endl;
                errorCount++;
                exit(1);
            } else if(branchName.find(32) != std::string::npos){ // if the branch name had a whitespace. Ex) branch name:
                std::cout << "Branch name has a whitespace ";
                if(OS)
                    std::cout << "@ln " << totalLineCount << " -> " << curLine << std::endl;
                else
                    std::cout << "@ln " << totalLineCount << " -> " << "\x1B[31m" << curLine << "\033[0m" << std::endl;
                errorCount++;
                exit(1);
            }
            else { // if this branch name was new, then add the branch to the map
                this->allBranches.insert(std::pair<std::string, int>(branchName, expressionCount));
            }
        }else{ // if current expression was not a branch expression
            expression.preprocess();
            this->allExpressions.insert(std::pair<uint32_t, std::string>(expressionCount, expression.getResultString()));
            expressionCount++;
        }
    }

    if(errorCount > 0){
        std::cout << "Failed to Assemble" << std::endl;
        std::cout << "Found " << errorCount << " errors" << std::endl;
        exit(1);
    }else{
        std::cout << "Successfully Assembled" << std::endl;
    }
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

bool FileReader::isDuplicateBranchName(std::string branchName) {
    for (auto const& x : this->allBranches){
        if (x.first == branchName) return true;
    }
    return false;
}
//
// @file : FileReader.cpp
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : A file that implements all member functions for class FileReader
// @date: 2022-03-16

#include "FileReader.h"


/**
 * A member function for class FileReader that retrieves current working directory
 * This looks for the last / or \ that separates directories and return all the string before / or \ as working directory.
 * @param curFile the current executable file in full directory
 * @return current working directory
 */
string FileReader::getCurrentDirectory(const string& curFile){
    for(uint32_t curPos = curFile.size() ; curPos >= 0 ; curPos--){
        if ((curFile.c_str()[curPos] == '/') || (curFile.c_str()[curPos] == '\\')){
            return curFile.substr(0, curPos);
        }
    }
    return "";
}

/**
 * A constructor member function for FileReader
 * This stores all expressions as string object in a queue, as well as making a map for branches
 * @param fileName the file directory to load file.
 */
FileReader::FileReader(const string& fileName) {
    this->fileObject = ifstream(fileName); // try loading it with absolute path
    uint32_t expressionCount = 0;

    if (!fileObject) { // if not loaded, try with relative path
        fileObject = ifstream(FileReader::getCurrentDirectory(fileName) + "/" + fileName);
        if (!fileObject) { // if relative path failed, exit
            cout << "[Error] Cannot locate file: " << fileName << endl;
            exit(1);
        }
    }

    while (!fileObject.eof()) {
        string curLine;
        getline(fileObject, curLine, '\n');
        curLine = preProcess(curLine);
        this->allExpressions.insert(pair<uint32_t, string>(expressionCount, curLine));
        expressionCount++;
    }
}

/**
 * A member function for class FileReader for removing comments from current expression string
 * @param expressionString the current expression string to remove comments from
 * @return string object that represents current expression without comments
 */
string FileReader::removeComments(const string& expressionString) {
    char* line = (char*)expressionString.c_str();
    uint16_t curPos = 0;
    while(line[curPos] != '\0'){
        if(line[curPos] == '#'){ // look for comments
            line[curPos] = '\0';
            break;
        }
        curPos++;
    }
    return line;
}

/**
 * A member function for class FileReader for removing indentation from current expression string
 * @param expressionString the current expression string to remove indentation from
 * @return string object that represents current expression without indentation
 */
string FileReader::removeTabs(const string& expressionString) {
    const char* line = expressionString.c_str();
    uint16_t curPos = 0;
    while ((line[curPos] == 32) || line[curPos] == 9) curPos++; // look for spaces and tabs
    return expressionString.substr(curPos, expressionString.size());
}

/**
 * A member function for class FileReader for removing duplicate whitespaces from current expression string
 * @param expressionString the current expression string to remove duplicate whitespaces from
 * @return string object that represents current expression without duplicate whitespaces
 */
string FileReader::removeDuplicateWhitespaces(const string& expressionString) {
    string copied = expressionString;
    string::iterator new_end = unique(copied.begin(), copied.end(),
                                                [](char lhs, char rhs) { return (lhs == rhs) && (lhs == ' '); });
    copied.erase(new_end, copied.end());
    return copied;
}

/**
 * A member function for class FileReader for adding a whitespace into the end of the expression string
 * @param expressionString the current expression string to add a whitespace into
 * @return string object that represents current expression with a whitespace added in the back
 */
string FileReader::addWhiteSpace(const string& expressionString) {
    const char* line = expressionString.c_str();
    if (line[expressionString.size() - 1] != 32){ // string's size just returns \0's index. So this is total len - 1
        // check if last character was a space, if it was not add one
        char* result = (char*)malloc(sizeof(char) * (expressionString.size() + 1)); // copy all
        for (uint32_t i = 0; i < expressionString.size() ; i++) result[i] = line[i];
        result[expressionString.size()] = 32; // add space
        result[expressionString.size() + 1] = '\0'; // add a \0
        return result;
    }
    return line;
}

/**
 * A member function for class FileReader for replacing tabs into whitespaces in a expression.
 * @param expressionString the current expression string to replace tabs into whitespaces
 * @return string object that represents current expression with tabs replaced into whitespaces
 */
string FileReader::replaceTabToWhitespaces(const string& expressionString) {
    string copied = expressionString;
    copied = regex_replace(expressionString, std::regex("\t"), " ");

    return copied;
}

/**
 * A member function for class FileReader for replacing commas into whitespaces in a expression.
 * @param expressionString the current expression string to replace commas into whitespaces
 * @return string object that represents current expression with commas replaced into whitespaces
 */
string FileReader::removeCommas(const string& expressionString) {
    string copied = expressionString;
    copied = regex_replace(expressionString, std::regex(","), " ");

    return copied;
}

/**
 * A member function for class FileReader for preprocessing current expression string before generating a expression.
 * This member function currently calls following preprocessing features.
 * removeTabs
 * removeComments
 * addWhiteSpace
 * replaceTabToWhitespaces
 * removeCommas
 * removeDuplicateWhitespaces
 * @param expressionString the current expression string to preprocess
 * @return string object that represents current expression that was preprocessed.
 */
string FileReader::preProcess(const string& expressionString) {
    string copied = expressionString;
    copied = removeTabs(copied);
    copied = removeComments(copied);
    copied = addWhiteSpace(copied);
    copied = replaceTabToWhitespaces(copied);
    copied = removeCommas(copied);
    copied = removeDuplicateWhitespaces(copied);

    return copied;
}

/**
 * A getter member function for attribute allExpressions
 * @return returns allExpression in map object
 */
map<uint32_t, string> FileReader::getAllExpressions() {
    return this->allExpressions;
}




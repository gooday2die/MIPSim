//
// @file : Expression.cpp
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : A file that implements all member functions for class Expression
// @date: 2022-03-12

#include "Expression.h"

#include <utility>

/**
 * A constructor member function for class Expression.
 * This removes comments and tabs from the expression automatically
 * @param argExpression string object that represents expression
 */
Expression::Expression(std::string argExpression) {
    this->expressionString = std::move(argExpression);
    this->removeComments();
    this->removeTabs();
}

/**
 * A member function for class Expression to check if current expression is a declaration of branch
 * @return returns true if current expression was declaration of branch, false if not
 */
bool Expression::isBranchExpression() {
    const char* line = this->expressionString.c_str();
    uint16_t curPos = 0;
    while(line[curPos] != '\0'){
        if(line[curPos] == ':') return true;
        else curPos++;
    }
    return false;
}

/**
 * A member function for class Expression to retrieve current expression's branch name
 * @return returns string object that represents the current branch's name
 */
std::string Expression::getBranchName() {
    const char* line = this->expressionString.c_str();
    uint16_t curPos = 0;
    while(line[curPos] != '\0'){
        if(line[curPos] == ':') return this->expressionString.substr(0, curPos);
        else curPos++;
    }
    return "";
}

/**
 * A member function for class Expression to preprocess the the code string object.
 * This member function does the following thing in order
 * - add a whitespace to the end of the expression if it does not have one
 * - set two or more consecutive whitespaces into just one whitespace
 */
void Expression::preprocess() {
    this->addWhiteSpace();
    this->makeOneWhiteSpace();
}

/**
 * A member function for class Expression that removes comments from the string object
 */
void Expression::removeComments() {
    char* line = (char*)this->expressionString.c_str();
    uint16_t curPos = 0;
    while(line[curPos] != '\0'){
        if(line[curPos] == '#'){ // look for comments
            line[curPos] = '\0';
            break;
        }
        curPos++;
    }
    this->expressionString = std::string(line);
}

/**
 * A member function for class Expression that removes tabs from the string object.
 * For example, the tabs can be represented using 4 spaces or just a \t tab word.
 * This member function removes both occurrences and replace with no character.
 */
void Expression::removeTabs() {
    const char* line = this->expressionString.c_str();
    uint16_t curPos = 0;
    while (line[curPos] == 32) curPos++; // look for spaces
    this->expressionString =  this->expressionString.substr(curPos, this->expressionString.size());

    curPos = 0;
    while (line[curPos] == 9) curPos++; // look for tabs
    this->expressionString =  this->expressionString.substr(curPos, this->expressionString.size());
}

/**
 * A member function for adding a single whitespace to the end of the string.
 * There is a wierd bug with the Translator class that without out a whitespace at the end of the string,
 * it cannot separate the arguments and registers while parsing. So this member function adds a whitespace to the
 * end of the string in order to prevent that little glitch.
 */
void Expression::addWhiteSpace() {
    const char* line = this->expressionString.c_str();
    if (line[this->expressionString.size() - 1] != 32){ // string's size just returns \0's index. So this is total len - 1
        // check if last character was a space, if it was not add one
        char* result = (char*)malloc(sizeof(char) * (this->expressionString.size() + 1)); // copy all
        for (uint32_t i = 0; i < this->expressionString.size() ; i++) result[i] = line[i];
        result[this->expressionString.size()] = 32; // add space
        result[this->expressionString.size() + 1] = '\0'; // add a \0
        this->expressionString = std::string(result);
    }
}

/**
 * A member function for setting two or more consecutive whitespaces into just one whitespace.
 * This member function uses lambada and the basic idea came from
 * https://stackoverflow.com/questions/8362094/replace-multiple-spaces-with-one-space-in-a-string
 */
void Expression::makeOneWhiteSpace() {
    std::string::iterator new_end = std::unique(this->expressionString.begin(), this->expressionString.end(),
                                                [](char lhs, char rhs) { return (lhs == rhs) && (lhs == ' '); });
    this->expressionString.erase(new_end, this->expressionString.end());
}


/**
 * A getter member function for getting the result string.
 * @return returns the result string object that represents preprocessed expression.
 */
std::string Expression::getString() const {
    return this->expressionString;
}

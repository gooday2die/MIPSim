//
// @file : SemanticAnalyzer.cpp
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : A file that implements all member functions for class SemanticAnalyzer
// @date: 2022-03-17

#include "SemanticAnalyzer.h"

/**
 * A constructor member function for SemanticAnalyzer.
 */
SemanticAnalyzer::SemanticAnalyzer() {
    ;
}

/**
 * A member function that checks if branch name was declared before
 * @param branchName the string object that represents branch's name
 * @return returns true if it was declared before, false if it was new
 */
bool SemanticAnalyzer::isDuplicateLabelName(const string& labelName) {
    for (auto const& x : this->allBranches){
        if(x == labelName) return true;
    }
    this->allBranches.emplace_back(labelName);
    return false;
}

/**
 * A member function for class SemanticAnalyzer that analyzes current instruction.
 * @param curInstruction pair of instruction string and token queue
 */
void SemanticAnalyzer::analyze(const pair<string, queue<Tokens>>& curInstruction) {
    string instructionString = curInstruction.first;
    queue<Tokens> tokenQueue = curInstruction.second;
    while (!tokenQueue.empty()){
        Tokens currentToken = tokenQueue.front();
        if (currentToken == Tokens::tLabel){
            instructionString = regex_replace(instructionString, std::regex(":"), "");
            if (this->isDuplicateLabelName(instructionString)) throw BranchExceptions::duplicateNameException();
        }
        tokenQueue.pop();
    }
}
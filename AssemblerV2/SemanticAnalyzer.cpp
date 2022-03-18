//
// @file : SemanticAnalyzer.cpp
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : A file that implements all member functions for class SemanticAnalyzer
//

#include "SemanticAnalyzer.h"

/**
 * A constructor member function for SemanticAnalyzer.
 */
SemanticAnalyzer::SemanticAnalyzer() {
    1;
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
 * A member function that gets section type and sets section type according to the section expression.
 * @param sectionString the string object that represents section's name
 */
void SemanticAnalyzer::getSectionType(const string& sectionString) {
    if (sectionString == ".text") this->sectionType = 1;
    else if (sectionString == ".data") this->sectionType = 2;
}

/**
 * A member function that gets if current expression is in right section.
 * This member function checks those cases:
 * 1. text section does not have data definition tokens
 * 2. data section does not have other expressions than data data definition tokens.
 * @param token the token value ot find out.
 * @return returns true if expression is in right place, false if not
 */
bool SemanticAnalyzer::isExpressionInRightSection(const Tokens& token) const{
    return (((this->sectionType == 1) && (token != Tokens::tDataDefinition))
            || ((this->sectionType == 2) && (token == Tokens::tDataDefinition)));
}

/**
 * A member function for class SemanticAnalyzer that analyzes current instruction.
 * The semantic analyzer works in following order
 * 1. Check if current token is a section token
 * 2. Check if current token is in right section (data or text section)
 * 3. Check if current token is a duplicate label name
 * @param curInstruction pair of instruction string and token queue
 */
void SemanticAnalyzer::analyze(const pair<string, queue<Tokens>>& curInstruction) {
    string instructionString = curInstruction.first;
    queue<Tokens> tokenQueue = curInstruction.second;

    while (!tokenQueue.empty()){
        Tokens currentToken = tokenQueue.front();

        if (currentToken == Tokens::tSection) {
            this->getSectionType(instructionString);
        } else{
            if (this->isExpressionInRightSection(currentToken)){
                if (currentToken == Tokens::tLabelDeclaration){
                    instructionString = regex_replace(instructionString, std::regex(":"), "");
                    if(this->isDuplicateLabelName(instructionString)) throw GrammarExceptions::duplicateLabelNameException();
                }
            } else{
                throw GrammarExceptions::tokenInWrongSection();
            }
        }

        tokenQueue.pop();
    }
}
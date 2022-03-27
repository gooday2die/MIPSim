//
// @file : SemanticAnalyzer.cpp
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : A file that implements all member functions for class SemanticAnalyzer
//

#include "SemanticAnalyzer.h"

/**
 * A constructor member function for SemanticAnalyzer.
 * This sets all available tokens in data section.
 */
SemanticAnalyzer::SemanticAnalyzer() {
    this->previousToken = Tokens::tUnknown;
    this->dataSectionTokens.emplace_back(Tokens::tDataDefinition);
    this->dataSectionTokens.emplace_back(Tokens::tString);
    this->dataSectionTokens.emplace_back(Tokens::tLabelDeclaration);

    this->textSectionTokens.emplace_back(Tokens::tSyscall);
    this->textSectionTokens.emplace_back(Tokens::tPseudoInstruction);
    this->textSectionTokens.emplace_back(Tokens::tInstructionMnemonic);
    this->textSectionTokens.emplace_back(Tokens::tLabelDeclaration);

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
    bool result1 = any_of(this->dataSectionTokens.begin(), this->dataSectionTokens.end(), [&token](auto const &x) {
        if (x == token) return true; return false;
    });

    bool result2 = any_of(this->textSectionTokens.begin(), this->textSectionTokens.end(), [&token](auto const &x) {
        if (x == token) return true; return false;
    });

    return (((this->sectionType == 1) && (result2))
            || ((this->sectionType == 2) && (result1)));
}

void SemanticAnalyzer::checkCorrectLabelDefinition(const queue<Tokens>& tokenQueue, const string& instructionString) {
    string copiedString = instructionString;
    queue<Tokens> copiedQueue = tokenQueue;
    string space_delimiter = " ";
    vector<string> words{};
    string labelName;

    size_t pos = 0;
    while ((pos = copiedString.find(space_delimiter)) != string::npos) { // split expression with whitespace
        words.push_back(copiedString.substr(0, pos));
        copiedString.erase(0, pos + space_delimiter.length());
    }

    if (words.empty()) labelName = instructionString;
    else labelName = regex_replace(words[0], std::regex(":"), "");

    if(this->isDuplicateLabelName(labelName)) throw GrammarExceptions::duplicateLabelNameException(); // check if duplicate label name

    if (this->sectionType == 1){ // if this was text section
        if((copiedQueue.size() - 1) == 0) return;
        else throw GrammarExceptions::invalidArgumentException();
    } else{ // if this was data section
        if(copiedQueue.size() != 3) throw GrammarExceptions::invalidArgumentException();
        else{
            copiedQueue.pop();
            Tokens first = copiedQueue.front();
            copiedQueue.pop();
            Tokens second = copiedQueue.front();

            if ((first == Tokens::tDataDefinition) && second == Tokens::tString) return;
            else throw GrammarExceptions::invalidArgumentException();
        }
    }
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
    Tokens currentToken = tokenQueue.front();

    if (currentToken == Tokens::tSection) { // if this was section definition, get section info.
        this->getSectionType(instructionString);
    } else{ // else, do following things
        if (this->isExpressionInRightSection(currentToken)){ // 1. check if current expression was in correct section
            if (currentToken == Tokens::tLabelDeclaration) {
                this->checkCorrectLabelDefinition(tokenQueue, instructionString); // 2. check if label declaration was correct
            }
        } else{
            throw GrammarExceptions::tokenInWrongSection();
        }
    }
}
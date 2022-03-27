//
// @file : SyntaxAnalyzer.cpp
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : A file that implements all member functions for class SyntaxAnalyzer
//

#include "SyntaxAnalyzer.h"


/**
 * A constructor member function that adds all syntax to syntax analyzer.
 */
SyntaxAnalyzer::SyntaxAnalyzer() {
    this->allSyntax.insert(pair<string, queue<Tokens>>());
    this->allSyntax.insert(pair<string, queue<Tokens>>("add", generateTokenQueue({Tokens::tInstructionMnemonic, Tokens::tRegister, Tokens::tRegister, Tokens::tRegister})));
    this->allSyntax.insert(pair<string, queue<Tokens>>("addu", generateTokenQueue({Tokens::tInstructionMnemonic, Tokens::tRegister, Tokens::tRegister, Tokens::tRegister})));
    this->allSyntax.insert(pair<string, queue<Tokens>>("and", generateTokenQueue({Tokens::tInstructionMnemonic, Tokens::tRegister, Tokens::tRegister, Tokens::tRegister})));
    this->allSyntax.insert(pair<string, queue<Tokens>>("nor", generateTokenQueue({Tokens::tInstructionMnemonic, Tokens::tRegister, Tokens::tRegister, Tokens::tRegister})));
    this->allSyntax.insert(pair<string, queue<Tokens>>("or", generateTokenQueue({Tokens::tInstructionMnemonic, Tokens::tRegister, Tokens::tRegister, Tokens::tRegister})));
    this->allSyntax.insert(pair<string, queue<Tokens>>("slt", generateTokenQueue({Tokens::tInstructionMnemonic, Tokens::tRegister, Tokens::tRegister, Tokens::tRegister})));
    this->allSyntax.insert(pair<string, queue<Tokens>>("sltu", generateTokenQueue({Tokens::tInstructionMnemonic, Tokens::tRegister, Tokens::tRegister, Tokens::tRegister})));
    this->allSyntax.insert(pair<string, queue<Tokens>>("sub", generateTokenQueue({Tokens::tInstructionMnemonic, Tokens::tRegister, Tokens::tRegister, Tokens::tRegister})));
    this->allSyntax.insert(pair<string, queue<Tokens>>("subu", generateTokenQueue({Tokens::tInstructionMnemonic, Tokens::tRegister, Tokens::tRegister, Tokens::tRegister})));
    this->allSyntax.insert(pair<string, queue<Tokens>>("jr", generateTokenQueue({Tokens::tInstructionMnemonic, Tokens::tRegister})));

    this->allSyntax.insert(pair<string, queue<Tokens>>("addi", generateTokenQueue({Tokens::tInstructionMnemonic, Tokens::tRegister, Tokens::tRegister, Tokens::tImmediate})));
    this->allSyntax.insert(pair<string, queue<Tokens>>("addiu", generateTokenQueue({Tokens::tInstructionMnemonic, Tokens::tRegister, Tokens::tRegister, Tokens::tImmediate})));
    this->allSyntax.insert(pair<string, queue<Tokens>>("andi", generateTokenQueue({Tokens::tInstructionMnemonic, Tokens::tRegister, Tokens::tRegister, Tokens::tImmediate})));
    this->allSyntax.insert(pair<string, queue<Tokens>>("ori", generateTokenQueue({Tokens::tInstructionMnemonic, Tokens::tRegister, Tokens::tRegister, Tokens::tImmediate})));
    this->allSyntax.insert(pair<string, queue<Tokens>>("slti", generateTokenQueue({Tokens::tInstructionMnemonic, Tokens::tRegister, Tokens::tRegister, Tokens::tImmediate})));
    this->allSyntax.insert(pair<string, queue<Tokens>>("sltiu", generateTokenQueue({Tokens::tInstructionMnemonic, Tokens::tRegister, Tokens::tRegister, Tokens::tImmediate})));

    this->allSyntax.insert(pair<string, queue<Tokens>>("beq", generateTokenQueue({Tokens::tInstructionMnemonic, Tokens::tRegister, Tokens::tRegister, Tokens::tDefinedLabel})));
    this->allSyntax.insert(pair<string, queue<Tokens>>("bne", generateTokenQueue({Tokens::tInstructionMnemonic, Tokens::tRegister, Tokens::tRegister, Tokens::tDefinedLabel})));

    this->allSyntax.insert(pair<string, queue<Tokens>>("sll", generateTokenQueue({Tokens::tInstructionMnemonic, Tokens::tRegister, Tokens::tRegister, Tokens::tImmediate})));
    this->allSyntax.insert(pair<string, queue<Tokens>>("srl", generateTokenQueue({Tokens::tInstructionMnemonic, Tokens::tRegister, Tokens::tRegister, Tokens::tImmediate})));
    this->allSyntax.insert(pair<string, queue<Tokens>>("j", generateTokenQueue({Tokens::tInstructionMnemonic, Tokens::tDefinedLabel})));
    this->allSyntax.insert(pair<string, queue<Tokens>>("jal", generateTokenQueue({Tokens::tInstructionMnemonic, Tokens::tDefinedLabel})));

    this->allSyntax.insert(pair<string, queue<Tokens>>("move", generateTokenQueue({Tokens::tPseudoInstruction, Tokens::tRegister, Tokens::tRegister})));
    this->allSyntax.insert(pair<string, queue<Tokens>>("li", generateTokenQueue({Tokens::tPseudoInstruction, Tokens::tRegister, Tokens::tImmediate})));
    this->allSyntax.insert(pair<string, queue<Tokens>>("blt", generateTokenQueue({Tokens::tPseudoInstruction, Tokens::tRegister, Tokens::tRegister, Tokens::tDefinedLabel})));
    this->allSyntax.insert(pair<string, queue<Tokens>>("ble", generateTokenQueue({Tokens::tPseudoInstruction, Tokens::tRegister, Tokens::tRegister, Tokens::tDefinedLabel})));
    this->allSyntax.insert(pair<string, queue<Tokens>>("bgt", generateTokenQueue({Tokens::tPseudoInstruction, Tokens::tRegister, Tokens::tRegister, Tokens::tDefinedLabel})));
    this->allSyntax.insert(pair<string, queue<Tokens>>("bge", generateTokenQueue({Tokens::tPseudoInstruction, Tokens::tRegister, Tokens::tRegister, Tokens::tDefinedLabel})));
}

/**
 * A member function for Syntax Analyzer that generates a queue of tokens with provided tokens
 * @param tokenList the list that contains tokens that should be added into token queue
 * @return returns queue of tokens.
 */
queue<Tokens> SyntaxAnalyzer::generateTokenQueue(const initializer_list<int> &tokenList) {
    queue<Tokens> resultQueue;
    for (auto x: tokenList)
        resultQueue.push((Tokens)x);
    return resultQueue;
}

/**
 * A member function for SyntaxAnalyzer that analyzes a single queue of tokens with its instructions.
 * This compares the original syntax queues and the expression queue that was given as arguments.
 * If the original syntax matches with the given instruction, syntax is considered correct.
 * Else, that means syntax was incorrect.
 * @param curInstruction the pair of string and token's queue
 */
void SyntaxAnalyzer::analyze(const pair<string, queue<Tokens>>& curInstruction) {
    queue<Tokens> syntax;
    string instructionString = curInstruction.first;
    queue<Tokens> expressionTokens = curInstruction.second;

    switch (expressionTokens.front()){
        case tUnknown:
            throw GrammarExceptions::unknownTokenException();
        case tLabelDeclaration:
            return; // When label was found, it means that we just declared a label.
        case tRegister:
            throw GrammarExceptions::bareRegisterException();
        case tImmediate:
            throw GrammarExceptions::bareImmediateValueException();
        case tDefinedLabel:
            throw GrammarExceptions::bareLabelException();
        case tDataDefinition:
            break;
        case tPseudoInstruction: {
            try {
                syntax = this->allSyntax.find(instructionString)->second;
            } catch (const std::exception &ex) {
                throw GrammarExceptions::unknownPseudoInstructionMnemonicException();
            }
            break;
        }
        case tInstructionMnemonic: {
            try {
                syntax = this->allSyntax.find(instructionString)->second;
            } catch (const std::exception &ex) {
                throw GrammarExceptions::unknownInstructionMnemonicException();
            }
            break;
        }
        case tSection: // for now just return.
        case tSyscall:
            return;
        case tString:
            throw GrammarExceptions::bareStringException();
    }

    while(!syntax.empty()){
        Tokens syntaxToken = syntax.front();
        Tokens expressionToken = expressionTokens.front();

        syntax.pop();
        expressionTokens.pop();

        if(syntaxToken != expressionToken){
            if(expressionToken == Tokens::tUnknown) throw GrammarExceptions::unknownTokenException();
            else throw GrammarExceptions::invalidArgumentException();
        }

        if (expressionTokens.size() == syntax.size()) return;
        // if token counts do not match after popping, arguments were set wrong.
        else throw GrammarExceptions::invalidArgumentException();
    }
}
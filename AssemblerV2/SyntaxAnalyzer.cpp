//
// @file : SyntaxAnalyzer.cpp
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : A file that implements all member functions for class SyntaxAnalyzer
// @date: 2022-03-17

#include "SyntaxAnalyzer.h"


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
    
    this->allSyntax.insert(pair<string, queue<Tokens>>("sll", generateTokenQueue()));
    this->allSyntax.insert(pair<string, queue<Tokens>>("srl", generateTokenQueue()));
    this->allSyntax.insert(pair<string, queue<Tokens>>("j", generateTokenQueue()));
    this->allSyntax.insert(pair<string, queue<Tokens>>("jal", generateTokenQueue()));
    this->allSyntax.insert(pair<string, queue<Tokens>>("move", generateTokenQueue()));
    this->allSyntax.insert(pair<string, queue<Tokens>>("li", generateTokenQueue()));
    this->allSyntax.insert(pair<string, queue<Tokens>>("blt", generateTokenQueue()));
    this->allSyntax.insert(pair<string, queue<Tokens>>("ble", generateTokenQueue()));
    this->allSyntax.insert(pair<string, queue<Tokens>>("bgt", generateTokenQueue()));
    this->allSyntax.insert(pair<string, queue<Tokens>>("bge", generateTokenQueue()));
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
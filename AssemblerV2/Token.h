//
// @file : Token.h
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : A file that defines each token types as enumeration
// @date: 2022-03-17

#ifndef MIPSIM_TOKEN_H
#define MIPSIM_TOKEN_H
#pragma once


/**
 * A enumeration that defines all tokens in a enumeration.
 * This will be used during Lexical Analysis and Syntax Analysis
 */
enum Tokens{
    tUnknown = 0,
    tSection = 1,
    tLabel = 2,
    tRegister = 3,
    tImmediate = 4,
    tInstructionMnemonic = 5,
    tDefinedLabel = 6,
    tDataDefinition = 7,
};

#endif //MIPSIM_TOKEN_H

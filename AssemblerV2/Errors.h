//
// @file : AssemblerErrors.h
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : A header file that defines all exception classes
//

#ifndef MIPSIM_ASSEMBLERERRORS_H
#define MIPSIM_ASSEMBLERERRORS_H
#pragma once

#include <exception>


class GrammarExceptions{
public:
    class unknownInstructionMnemonicException : public std::exception{
    };

    class invalidArgumentException : public std::exception{
    };

    class unknownTokenException : public std::exception{
    };

    class bareImmediateValueException : public std::exception{
    };

    class bareRegisterException : public std::exception{
    };

    class bareLabelException : public std::exception{
    };

    class tokenInWrongSection : public std::exception{
    };

    class duplicateLabelNameException : public ::std::exception {
    };

    class whitespaceLabelNameException : public ::std::exception {
    };

    class emptyLabelNameException : public ::std::exception {
    };

    class unknownPseudoInstructionMnemonicException : public ::std::exception {
    };
};

class TranslatorExceptions{
public:
    class cannotFindRegisterIndexException : public ::std::exception {
    };
};


class BranchExceptions {
public:

class whitespaceNameException : public std::exception {
};

class emptyNameException : public std::exception{
};
};



#endif //MIPSIM_ASSEMBLERERRORS_H

//
// @file : AssemblerErrors.h
// @author : Gooday2die (Isu Kim)
// @Contacts : edina00@naver.com
// @brief : A header file that defines all exception classes
//

#ifndef MIPSIM_ASSEMBLERERRORS_H
#define MIPSIM_ASSEMBLERERRORS_H
#pragma once

#include <exception>


/**
 * A class for defining all grammatical exceptions (includes syntax errors)
 */
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

    class bareStringException : public std::exception{
    };

    class bareLabelDefinitionException : public std::exception{
    };

    class tokenInWrongSection : public std::exception{
    };

    class duplicateLabelNameException : public std::exception {
    };

    class whitespaceLabelNameException : public std::exception {
    };

    class emptyLabelNameException : public std::exception {
    };

    class unknownPseudoInstructionMnemonicException : public std::exception {
    };
};

/**
 * A class that defines all translator exceptions
 */
class TranslatorExceptions{
public:
    class cannotFindRegisterIndexException : public std::exception {
    };
    class cannotTranslateImmediateException : public std::exception{
    };
    class cannotFindInstructionMnemonicException : public std::exception{
    };
    class unexpectedInstructionArgumentTokenException : public std::exception{
    };
    class unexpectedInstructionTokenTypeException : public std::exception{
    };
    class cannotFindLabelNameException : public std::exception{
    };
};

/**
 * A class for branch exceptions. Is depreciated
 */
class BranchExceptions {
public:
    class whitespaceNameException : public std::exception {
    };
    class emptyNameException : public std::exception{
    };
};



#endif //MIPSIM_ASSEMBLERERRORS_H

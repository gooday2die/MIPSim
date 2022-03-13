//
// @file : AssemblerErrors.
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : 
// @date: 2022-03-12

#ifndef MIPSIM_ASSEMBLERERRORS_H
#define MIPSIM_ASSEMBLERERRORS_H
#pragma once

#include <exception>


class ExpressionExceptions{
public:
class unknownRegisterException : public std::exception{
};

class unknownInstructionMnemonicException : public std::exception{
};

class invalidArgumentException : public std::exception{

};
};
class BranchExceptions {
public:
class duplicateNameException : public ::std::exception {
};

class whitespaceNameException : public std::exception {
};

class emptyNameException : public std::exception{
};
};



#endif //MIPSIM_ASSEMBLERERRORS_H
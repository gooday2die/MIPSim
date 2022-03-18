//
// @file : Messages.h
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : A header file that defines all messages.
//

#ifndef MIPSIM_MESSAGES_H
#define MIPSIM_MESSAGES_H
#pragma once

// Windows don't deserve color output. :b
#ifdef _WIN32
#define ERROR_TAG "[ERROR]"
#define ASSEMBLE_FAILED "Failed to assemble"
#define ASSEMBLE_SUCCESS "Successfully assembled"
#define ERROR_EXPRESSION errorExpression
#endif


// Linux deserves color output. :)
#ifdef linux
#define ERROR_TAG "\x1B[31m[ERROR]\033[0m"
#define ASSEMBLE_FAILED "\x1B[31mFailed to assemble\033[0m"
#define ASSEMBLE_SUCCESS "\x1B[32mSuccessfully assembled\033[0m"
#define ERROR_EXPRESSION "\x1B[93m" << errorExpression << "\033[0m"
#endif

#endif //MIPSIM_MESSAGES_H

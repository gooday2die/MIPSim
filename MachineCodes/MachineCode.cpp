//
// @file : MachineCode.cpp
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : A file that implements all MachineCode member functions
// @date: 2022-03-07

#include "MachineCode.h"

MachineCode::MachineCode(int argCode, uint8_t argType) {
    this->code = argCode;
    this->codeType = argType;
}

uint8_t MachineCode::getCodeType() {
    return this->codeType;
}

int MachineCode::getcode() {
    return this->code;
}
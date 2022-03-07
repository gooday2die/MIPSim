//
// @file : Instructions.cpp
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : A file that implements all member functions from class Instructions
// @date: 2022-03-07

#include "Instructions.h"

/**
 * A member function for instruction "add"
 * @param rs the rs register
 * @param rt the rt register
 * @param rd the rd register
 */
void Instructions::_add::execute(Register rs, Register rt, Register rd) {
    int rsVal = rs.getValue();
    int rtVal = rt.getValue();
    long rdVal = rsVal + rtVal;

    if (rdVal > 0xFFFFFFFF) throw std::overflow_error("Integer Overflow with operation add");
    else rd.setValue(rdVal);
}
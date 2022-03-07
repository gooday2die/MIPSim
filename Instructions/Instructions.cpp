//
// @file : Instructions.cpp
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : A file that implements all member functions from class Instructions
// @date: 2022-03-07

#include "Instructions.h"

/**
 * A member function for instruction 'add'
 * As MIPS's instruction raises exception when integer overflow happens, this throws overflow_error
 * @param rs the pointer address rs register's Register Object
 * @param rt the pointer address rt register's Register Object
 * @param rd the pointer address rd register's Register Object
 */
void Instructions::RType::_add(Register* rs, Register* rt, Register* rd) {
    long rsVal = rs->getValue();
    long rtVal = rt->getValue();
    if ((rsVal > 0) && (rtVal > INT_MAX - rsVal))
        throw std::overflow_error("Integer Overflow with operation add");
    else rd->setValue(rsVal + rtVal);
}

/**
 * A member function for instruction addu'
 * @param rs the pointer address rs register's Register Object
 * @param rt the pointer address rt register's Register Object
 * @param rd the pointer address rd register's Register Object
 */
void Instructions::RType::_addu(Register* rs, Register* rt, Register* rd) {
    int rsVal = rs->getValue();
    int rtVal = rt->getValue();
    rd->setValue(rsVal + rtVal);
}

/**
 * A member function for instruction 'and'
 * @param rs the pointer address rs register's Register Object
 * @param rt the pointer address rt register's Register Object
 * @param rd the pointer address rd register's Register Object
 */
void Instructions::RType::_and(Register* rs, Register* rt, Register* rd) {
    int rsVal = rs->getValue();
    int rtVal = rt->getValue();
    rd->setValue(rsVal & rtVal);
}

/**
 * A member function for instruction 'addi'
 * As MIPS's instruction raises exception when integer overflow happens, this throws overflow_error
 * @param rs the pointer address rs register's Register Object
 * @param rt the pointer address rt register's Register Object
 * @param imm the uint16_t type of immediate value
 */
void Instructions::IType::_addi(Register* rs, Register* rt, uint16_t imm) {
    int rsVal = rs->getValue();
    if ((rsVal > 0) && (imm > INT_MAX - rsVal)) throw std::overflow_error("Integer Overflow with operation addi");
    else rt->setValue(rsVal + imm);
}

/**
 * A member function for instruction 'addiu'
 * @param rs the pointer address rs register's Register Object
 * @param rt the pointer address rt register's Register Object
 * @param imm the uint16_t type of immediate value
 */
void Instructions::IType::_addiu(Register* rs, Register* rt, uint16_t imm) {
    int rsVal = rs->getValue();
    rt->setValue(rsVal + imm);
}

/**
 * A member function for instruction 'andi'
 * @param rs the pointer address rs register's Register Object
 * @param rt the pointer address rt register's Register Object
 * @param imm the uint16_t type of immediate value
 */
void Instructions::IType::_andi(Register* rs, Register* rt, uint16_t imm) {
    int rsVal = rs->getValue();
    rt->setValue(rsVal & imm);
}
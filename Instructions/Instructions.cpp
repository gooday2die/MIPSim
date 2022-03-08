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

/**
 * A member function for instruction 'nor'
 * @param rs the pointer address rs register's Register Object
 * @param rt the pointer address rt register's Register Object
 * @param rd the pointer address rd register's Register Object
 */
void Instructions::RType::_nor(Register* rs, Register* rt, Register* rd) {
    int rsVal = rs->getValue();
    int rtVal = rt->getValue();
    rd->setValue(~(rsVal | rtVal));
}

/**
 * A member function for instruction 'or'
 * @param rs the pointer address rs register's Register Object
 * @param rt the pointer address rt register's Register Object
 * @param rd the pointer address rd register's Register Object
 */
void Instructions::RType::_or(Register* rs, Register* rt, Register* rd) {
    int rsVal = rs->getValue();
    int rtVal = rt->getValue();
    rd->setValue(rsVal | rtVal);
}

/**
 * A member function for instruction 'ori'
 * @param rs the pointer address rs register's Register Object
 * @param rt the pointer address rt register's Register Object
 * @param imm the uint16_t type of immediate value
 */
void Instructions::IType::_ori(Register* rs, Register* rt, uint16_t imm) {
    int rsVal = rs->getValue();
    rt->setValue(rsVal | imm);
}

/**
 * A member function for instruction 'slt'
 * @param rs the pointer address rs register's Register Object
 * @param rt the pointer address rt register's Register Object
 * @param rd the pointer address rd register's Register Object
 */
void Instructions::RType::_slt(Register* rs, Register* rt, Register* rd) {
    int rsVal = rs->getValue();
    int rtVal = rt->getValue();
    rd->setValue(rsVal < rtVal);
}

/**
 * A member function for instruction 'slti'
 * @param rs the pointer address rs register's Register Object
 * @param rt the pointer address rt register's Register Object
 * @param imm the uint16_t type of immediate value
 */
void Instructions::IType::_slti(Register* rs, Register* rt, uint16_t imm) {
    int rsVal = rs->getValue();
    rt->setValue(rsVal < (signed int) imm);
}

/**
 * A member function for instruction 'sltiu'
 * @param rs the pointer address rs register's Register Object
 * @param rt the pointer address rt register's Register Object
 * @param imm the uint16_t type of immediate value
 */
void Instructions::IType::_sltiu(Register* rs, Register* rt, uint16_t imm) {
    int rsVal = rs->getValue();
    rt->setValue((unsigned int)rsVal < imm);
}

/**
 * A member function for instruction 'sltu'
 * @param rs the pointer address rs register's Register Object
 * @param rt the pointer address rt register's Register Object
 * @param rd the pointer address rd register's Register Object
 */
void Instructions::RType::_sltu(Register* rs, Register* rt, Register* rd) {
    int rsVal = rs->getValue();
    int rtVal = rt->getValue();
    rd->setValue((unsigned int) rsVal < (unsigned int)rtVal);
}

/**
 * A member function for instruction 'sub'
 * As MIPS's instruction raises exception when integer overflow happens, this throws overflow_error
 * For example, when rs was positive, rt was negative this works just like rs + rt. This might be overflowed
 * @param rs the pointer address rs register's Register Object
 * @param rt the pointer address rt register's Register Object
 * @param rd the pointer address rd register's Register Object
 */
void Instructions::RType::_sub(Register* rs, Register* rt, Register* rd) {
    long rsVal = rs->getValue();
    long rtVal = rt->getValue();
    if ((rsVal < 0) && (rtVal > INT_MAX - rsVal))
        throw std::overflow_error("Integer Overflow with operation sub");
    else rd->setValue(rsVal - rtVal);
}

/**
 * A member function for instruction subu'
 * @param rs the pointer address rs register's Register Object
 * @param rt the pointer address rt register's Register Object
 * @param rd the pointer address rd register's Register Object
 */
void Instructions::RType::_subu(Register* rs, Register* rt, Register* rd) {
    int rsVal = rs->getValue();
    int rtVal = rt->getValue();
    rd->setValue(rsVal - rtVal);
}

/**
 * A member function for instruction j
 * @param pc PC Register's pointer
 * @param address the address
 */
void Instructions::JType::_j(Register* pc, uint32_t address) {
    pc->setValue(address);
}

/**
 * A member function for instruction jal
 * @param pc PC Register's pointer
 * @param ra $31 Register($ra)'s address
 * @param address the address
 */
 void Instructions::JType::_jal(Register* pc, Register* ra, uint32_t address){
    ra->setValue(pc->getValue() + 8);
    pc->setValue(address);
}

/**
 * A member function for instruction jr
 * @param pc PC Register's pointer
 * @param rs $rs Register's pointer
 */
void Instructions::RType::_jr(Register* pc, Register* rs){
    pc->setValue(rs->getValue());
}

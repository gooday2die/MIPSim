//
// @file : Instructions.cpp
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : A file that implements all member functions from class Instructions
//

#include "Instructions.h"

/**
 * A member function for instruction 'add'
 * As MIPS's instruction raises exception when integer overflow happens, this throws overflow_error
 * @param rs integer value of rs register
 * @param rt integer value of rt register
 * @param rd the pointer address rd register's Register Object
 */
void Instructions::RType::_add(uint32_t rs, uint32_t rt, uint32_t* rd) {
    if ((rs > 0) && (rt > INT_MAX - rs))
        throw std::overflow_error("Integer Overflow with instruction add");
    else *rd = rs + rt;
}

/**
 * A member function for instruction 'addu'
 * @param rs integer value of rs register
 * @param rt integer value of rt register
 * @param rd the pointer address rd register's Register Object
 */
void Instructions::RType::_addu(uint32_t rs, uint32_t rt, uint32_t* rd) {
    *rd = rs + rt;
}

/**
 * A member function for instruction 'and'
 * @param rs integer value of rs register
 * @param rt integer value of rt register
 * @param rd the pointer address rd register's Register Object
 */
void Instructions::RType::_and(uint32_t rs, uint32_t rt, uint32_t* rd) {
    *rd = rs & rt;
}

/**
 * A member function for instruction 'addi'
 * As MIPS's instruction raises exception when integer overflow happens, this throws overflow_error
 * @param rs integer value of rs register
 * @param rt integer value of rt register
 * @param imm the uint16_t type of immediate value
 */
void Instructions::IType::_addi(uint32_t rs, uint32_t* rt, uint16_t imm) {
    if ((rs > 0) && (imm > INT_MAX - rs))
        throw std::overflow_error("Integer Overflow with instruction add");
    else *rt = rs + imm;
}

/**
 * A member function for instruction 'addiu'
 * @param rs integer value of rs register
 * @param rt the pointer address rt register's value
 * @param imm the uint16_t type of immediate value
 */
void Instructions::IType::_addiu(uint32_t rs, uint32_t* rt, uint16_t imm) {
    *rt = rs + imm;
}

/**
 * A member function for instruction 'andi'
 * @param rs integer value of rs register
 * @param rt the pointer address rt register's value
 * @param imm the uint16_t type of immediate value
 */
void Instructions::IType::_andi(uint32_t rs, uint32_t* rt, uint16_t imm) {
    uint32_t rsVal = rs;
    *rt = rs & imm;
}

/**
 * A member function for instruction 'nor'
 * @param rs integer value of rs register
 * @param rt integer value of rt register
 * @param rd the pointer address rd register's Register Object
 */
void Instructions::RType::_nor(uint32_t rs, uint32_t rt, uint32_t* rd) {
    *rd = ~(rs | rt);
}

/**
 * A member function for instruction 'or'
 * @param rs integer value of rs register
 * @param rt integer value of rt register
 * @param rd the pointer address rd register's Register Object
 */
void Instructions::RType::_or(uint32_t rs, uint32_t rt, uint32_t* rd) {
    *rd = (rs | rt);
}

/**
 * A member function for instruction 'ori'
 * @param rs integer value of rs register
 * @param rt the pointer address rt register's value
 * @param imm the uint16_t type of immediate value
 */
void Instructions::IType::_ori(uint32_t rs, uint32_t* rt, uint16_t imm) {
    *rt = rs | imm;
}

/**
 * A member function for instruction 'slt'
 * @param rs integer value of rs register
 * @param rt integer value of rt register
 * @param rd the pointer address rd register's Register Object
 */
void Instructions::RType::_slt(uint32_t rs, uint32_t rt, uint32_t* rd) {
    *rd = (signed int)rs < (signed int)rt;
}

/**
 * A member function for instruction 'slti'
 * @param rs integer value of rs register
 * @param rt the pointer address rt register's value
 * @param imm the uint16_t type of immediate value
 */
void Instructions::IType::_slti(uint32_t rs, uint32_t* rt, uint16_t imm) {
    *rt = (signed int)rs < (signed int) imm;
}

/**
 * A member function for instruction 'sltiu'
 * @param rs integer value of rs register
 * @param rt the pointer address rt register's value
 * @param imm the uint16_t type of immediate value
 */
void Instructions::IType::_sltiu(uint32_t rs, uint32_t* rt, uint16_t imm) {
    *rt = rs < imm;
}

/**
 * A member function for instruction 'sltu'
 * @param rs integer value of rs register
 * @param rt integer value of rt register
 * @param rd the pointer address rd register's Register Object
 */
void Instructions::RType::_sltu(uint32_t rs, uint32_t rt, uint32_t* rd) {
    *rd = rs < rt;
}

/**
 * A member function for instruction 'sub'
 * As MIPS's instruction raises exception when integer overflow happens, this throws overflow_error
 * For example, when rs was positive, rt was negative this works just like rs + rt. This might be overflowed
 * @param rs integer value of rs register
 * @param rt integer value of rt register
 * @param rd the pointer address rd register's Register Object
 */
void Instructions::RType::_sub(uint32_t rs, uint32_t rt, uint32_t* rd) {
    long rsVal = (signed int)rs;
    long rtVal = (signed int)rt;
    if ((rtVal < 0) && (rsVal > INT_MAX - rtVal))
        throw std::overflow_error("Integer Overflow with operation sub");
    else *rd = rs - rt;
}

/**
 * A member function for instruction 'subu'
 * @param rs integer value of rs register
 * @param rt integer value of rt register
 * @param rd the pointer address rd register's Register Object
 */
void Instructions::RType::_subu(uint32_t rs, uint32_t rt, uint32_t* rd) {
    *rd = rs - rt;
}

/**
 * A member function for instruction 'j'
 * @param pc PC Register's pointer
 * @param address the address
 */
void Instructions::JType::_j(uint32_t* pc, uint32_t address) {
    *pc = address;
}

/**
 * A member function for instruction 'jal'
 * @param pc PC Register's pointer
 * @param ra $31 Register($ra)'s address
 * @param address the address
 */
 void Instructions::JType::_jal(uint32_t* pc, uint32_t* ra, uint32_t address){
    *ra = *pc + 8;
    *pc = address;
}

/**
 * A member function for instruction 'jr'
 * @param pc PC Register's pointer
 * @param rs $rs Register's pointer
 */
void Instructions::RType::_jr(uint32_t* pc, uint32_t rs){
    *pc = rs;
}

/**
 * A member function for instruction 'sll'
 * @param pc PC Register's pointer
 * @param rs $rs Register's pointer
 */
void Instructions::RType::_sll(uint32_t rt, uint32_t* rd, uint8_t shamt){
    *rd = rt << shamt;
}

/**
 * A member function for instruction 'srl'
 * @param pc PC Register's pointer
 * @param rs $rs Register's pointer
 */
void Instructions::RType::_srl(uint32_t rt, uint32_t* rd, uint8_t shamt){
    *rd = rt >> shamt;
}

/**
 * A member function for instruction 'beq'
 * @param rs the rs register value
 * @param rt the rt register value
 * @param branchAddr the branch address to set pc
 * @param pc the pointer of pc
 */
void Instructions::IType::_beq(uint32_t rs, uint32_t rt, uint32_t branchAddr, uint32_t* pc) {
    if (rs == rt) *pc = branchAddr;
}

/**
 * A member function for instruction 'beq'
 * @param rs the rs register value
 * @param rt the rt register value
 * @param branchAddr the branch address to set pc
 * @param pc the pointer of pc
 */
void Instructions::IType::_bne(uint32_t rs, uint32_t rt, uint32_t branchAddr, uint32_t* pc) {
    if (rs != rt) *pc = branchAddr;
}
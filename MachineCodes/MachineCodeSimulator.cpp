//
// @file : MachineCodeSimulator.cpp
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : A file that implements all member functions for class MachineCodeSimulator
// @date: 2022-03-07

#include "MachineCodeSimulator.h"

/**
 * A constructor member function for MachineCodeSimulator
 * @param argRegisterHandler the RegisterHandler object for this machine code simulator
 */
MachineCodeSimulator::MachineCodeSimulator(RegisterHandler* argRegisterHandler) {
    this->registerHandler = argRegisterHandler;
}

/**
 * A member function that sets branches to the machine code simulator
 * @param branches the total branches's pointer
 */
void MachineCodeSimulator::setBranches(uint32_t* argBranches) {
    this->branches = argBranches;
    this->branchCount = this->getBranchCount();
}

/**
 * A member function for class MachineCodeSimulator for executing a single machine code
 * @param curCode the uint32_t type machine code.
 */
void MachineCodeSimulator::executeCode(uint32_t curCode) {
    uint8_t opcode = curCode >> 26; // OPCode's length = 6bit < 8bit
    uint8_t codeType;

    switch(opcode){ // parse CodeType
        case 0x00:
        case 0x10:
            codeType = 1; // R Type
            break;
        case 0x02:
        case 0x03:
            codeType = 3; // J Type
            break;
        default:
            codeType = 2; // I Type
    }

    switch(codeType) {
        case 1: {
            // R Type
            uint8_t rs = (curCode >> 21) & 0x1F; // rs length = 5bit < 8bit
            uint8_t rt = (curCode >> 16) & 0x1F; // rt length = 5bit < 8bit
            uint8_t rd = (curCode >> 11) & 0x1F; // rd length = 5bit < 8bit
            uint8_t shamt = (curCode >> 6) & 0x1F; // shamt length = 5bit < 8bit
            uint8_t funct = curCode & 0x3F; // funct length 6 bit < 8bit

            //printf("R TYPE : rs : %d / rt : %d / rd : %d / shamt : %d / funct : %d\n", rs, rt, rd, shamt, funct);
            switch (opcode) {
                case 0x00: {
                    switch (funct) {
                        case 0x20: // add instruction
                            Instructions::RType::_add(*registerHandler->getRegister(rs), *registerHandler->getRegister(rt),
                                                      registerHandler->getRegister(rd));
                            break;
                        case 0x21: // addu instruction
                            Instructions::RType::_addu(*registerHandler->getRegister(rs), *registerHandler->getRegister(rt),
                                                       registerHandler->getRegister(rd));
                            break;
                        case 0x22: // sub instruction
                            Instructions::RType::_sub(*registerHandler->getRegister(rs), *registerHandler->getRegister(rt),
                                                      registerHandler->getRegister(rd));
                            break;
                        case 0x23: // subu instruction
                            Instructions::RType::_subu(*registerHandler->getRegister(rs), *registerHandler->getRegister(rt),
                                                       registerHandler->getRegister(rd));
                            break;
                        case 0x24: // addu instruction
                            Instructions::RType::_and(*registerHandler->getRegister(rs), *registerHandler->getRegister(rt),
                                                      registerHandler->getRegister(rd));
                            break;
                        case 0x27: // nor instruction
                            Instructions::RType::_nor(*registerHandler->getRegister(rs), *registerHandler->getRegister(rt),
                                                      registerHandler->getRegister(rd));
                            break;
                        case 0x25: // or instruction
                            Instructions::RType::_or(*registerHandler->getRegister(rs), *registerHandler->getRegister(rt),
                                                     registerHandler->getRegister(rd));
                            break;
                        case 0x2a: // slt instruction
                            Instructions::RType::_slt(*registerHandler->getRegister(rs), *registerHandler->getRegister(rt),
                                                      registerHandler->getRegister(rd));
                            break;
                        case 0x2b: // sltu instruction
                            Instructions::RType::_sltu(*registerHandler->getRegister(rs), *registerHandler->getRegister(rt),
                                                       registerHandler->getRegister(rd));
                            break;
                        case 0x08: // jr instruction
                            Instructions::RType::_jr(registerHandler->getPC(), *registerHandler->getRegister(rs));
                            break;
                        case 0x00: // sll instruction
                            Instructions::RType::_sll(*registerHandler->getRegister(rt), registerHandler->getRegister(rd), shamt);
                            break;
                        case 0x02: // srl instruction
                            Instructions::RType::_srl(*registerHandler->getRegister(rt), registerHandler->getRegister(rd), shamt);
                            break;
                        default:
                            throw std::range_error("Unknown Operation");
                    }
                }
                    break;
                default:
                    throw std::range_error("Unknown Operation");
            }
            break;
        }
        case 2: {
            // I Type
            uint8_t rs = (curCode >> 21) & 0x1F; // rs length = 5bit < 8bit
            uint8_t rt = (curCode >> 16) & 0x1F; // rt length = 5bit < 8bit
            uint16_t imm = curCode & 0xFFFF; // imm length = 16 bit
            //printf("I TYPE : rs : %d / rt : %d / imm : %d\n", rs, rt, imm);
            switch (opcode) {
                case 0x08: // addi instruction
                    Instructions::IType::_addi(*registerHandler->getRegister(rs), registerHandler->getRegister(rt), imm);
                    break;
                case 0x09: // addiu instruction
                    Instructions::IType::_addiu(*registerHandler->getRegister(rs), registerHandler->getRegister(rt), imm);
                    break;
                case 0x0C: // andi instruction
                    Instructions::IType::_andi(*registerHandler->getRegister(rs), registerHandler->getRegister(rt), imm);
                    break;
                case 0x0D: // ori instruction
                    Instructions::IType::_ori(*registerHandler->getRegister(rs), registerHandler->getRegister(rt), imm);
                    break;
                case 0x0A: // stli instruction
                    Instructions::IType::_slti(*registerHandler->getRegister(rs), registerHandler->getRegister(rt), imm);
                    break;
                case 0x0B: // stliu instruction
                    Instructions::IType::_sltiu(*registerHandler->getRegister(rs), registerHandler->getRegister(rt), imm);
                    break;
                case 0x04: //beq instruction
                    Instructions::IType::_beq(*registerHandler->getRegister(rs), *registerHandler->getRegister(rt),
                                                   imm, registerHandler->getPC());
                    break;
                case 0x05: //bne instruction
                    Instructions::IType::_bne(*registerHandler->getRegister(rs), *registerHandler->getRegister(rt),
                                              imm, registerHandler->getPC());
                    break;
                default:
                    throw std::range_error("Unknown Operation");
            }
            break;
        }
        case 3: {
            // J Type
            uint32_t address = (curCode & 0x3FFFFFF);
            switch (opcode) {
                case 0x02: // j instruction
                    Instructions::JType::_j(registerHandler->getPC(), address);
                    break;
                case 0x03: // jal instruction
                    Instructions::JType::_jal(registerHandler->getPC(), registerHandler->getRegister(31), address);
                    break;
                default:
                    throw std::range_error("Unknown Operation");
            }
            break;
        }
        default:
            break;
    }
}

/**
 * A member function that counts total branches.
 * The last branch MUST contain 0xFFFFFFFF as it's value so that the branches are over.
 * @return total Count of Branches.
 */
uint16_t MachineCodeSimulator::getBranchCount() {
    uint16_t totalBranches = 0;
    while (this->branches[totalBranches] != 0xFFFFFFFF){
        totalBranches++;
    }
    return totalBranches;
}

uint32_t MachineCodeSimulator::getPC(){
    return *this->registerHandler->getPC();
}
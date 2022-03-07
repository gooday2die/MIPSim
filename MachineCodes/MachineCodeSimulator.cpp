//
// @file : MachineCodeSimulator.cpp
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : A file that implements all member functions for class MachineCodeSimulator
// @date: 2022-03-07

#include "MachineCodeSimulator.h"

MachineCodeSimulator::MachineCodeSimulator(RegisterHandler argRegisterHandler) {
    this->registerHandler = argRegisterHandler;
}

void MachineCodeSimulator::executeCode(MachineCode code) {
    int curCode = code.getcode();
    uint8_t codeType = code.getCodeType();

    uint8_t opcode = curCode >> 26; // OPCode's length = 6bit < 8bit

    switch(codeType){
        case 1:{
            // R Type
            uint8_t rs = (curCode >> 21) & 0x1F; // rs length = 5bit < 8bit
            uint8_t rt = (curCode >> 16) & 0x1F; // rt length = 5bit < 8bit
            uint8_t rd = (curCode >> 11) & 0x1F; // rd length = 5bit < 8bit
            uint8_t shamt = (curCode >> 6) & 0x1F; // shamt length = 5bit < 8bit
            uint8_t funct = curCode & 0x3F; // funct length 6 bit < 8bit

            //printf("R TYPE : rs : %d / rt : %d / rd : %d / shamt : %d / funct : %d\n", rs, rt, rd, shamt, funct);
            switch(opcode){
                case 0x00: {
                    switch(funct){
                        case 0x20: // add instruction
                            Instructions::RType::_add(registerHandler.getRegister(rs), registerHandler.getRegister(rt), registerHandler.getRegister(rd));
                            break;
                        case 0x21: // addu instruction
                            Instructions::RType::_addu(registerHandler.getRegister(rs), registerHandler.getRegister(rt), registerHandler.getRegister(rd));
                            break;
                        case 0x24: // and instruction
                            Instructions::RType::_and(registerHandler.getRegister(rs), registerHandler.getRegister(rt), registerHandler.getRegister(rd));
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
        case 2:{
            // I Type
            uint8_t rs = (curCode >> 21) & 0x1F; // rs length = 5bit < 8bit
            uint8_t rt = (curCode >> 16) & 0x1F; // rt length = 5bit < 8bit
            uint16_t imm = curCode & 0xFFFF; // imm length = 16 bit
            //printf("I TYPE : rs : %d / rt : %d / imm : %d\n", rs, rt, imm);
            switch(opcode){
                case 0x08:
                    Instructions::IType::_addi(registerHandler.getRegister(rs), registerHandler.getRegister(rt), imm);
                    break;
                case 0x09:
                    Instructions::IType::_addiu(registerHandler.getRegister(rs), registerHandler.getRegister(rt), imm);
                    break;
                case 0x0C:
                    Instructions::IType::_andi(registerHandler.getRegister(rs), registerHandler.getRegister(rt), imm);
                    break;
                default:
                    throw std::range_error("Unknown Operation");
            }
            break;
        }
        case 3: // J type
            ;
            break;
    }
}
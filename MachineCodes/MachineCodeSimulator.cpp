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

int MachineCodeSimulator::executeCode(MachineCode code) {
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

            switch(opcode){
                case 0x00: {
                    switch(funct){
                        case 0x20:{ // add instruction
                        }
                    }
                }

            }
            break;
        }
        case 2: // I Type
            ;
            break;
        case 3: // J type
            ;
            break;
    }
}
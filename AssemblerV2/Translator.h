//
// @file : Translator.
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : 
//

#ifndef MIPSIM_TRANSLATOR_H
#define MIPSIM_TRANSLATOR_H


enum Mnemonic{
    _add = 0x00000020,
    _addi = 0x20000000,
    _addiu = 0x24000000,
    _addu = 0x00000021,
    _and = 0x00000024,
    _andi = 0x30000000,
    _beq = 0x10000000,
    _bne = 0x14000000,
    _j = 0x08000000,
    _jal = 0x0c000000,
    _jr = 0x00000008,
    _nor = 0x00000027,
    _or = 0x00000025,
    _ori = 0x34000000,
    _slt = 0x0000002a,
    _slti = 0x28000000,
    _sltiu = 0x2c000000,
    _sltu = 0x0000002b,
    _sll = 0x00000000,
    _srl = 0x00000002,
    _sub = 0x00000022,
    _subu = 0x00000023,
};

class Translator {

};


#endif //MIPSIM_TRANSLATOR_H
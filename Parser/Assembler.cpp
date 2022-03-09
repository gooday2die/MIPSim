//
// @file : Assembler.
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : 
// @date: 2022-03-09

#include "Assembler.h"

uint32_t Assembler::generateMachineCode(const char* expression) {
    std::string s = expression;
    uint8_t registerCount = std::count(s.begin(), s.end(), '$'); // count how many $ exists.
    uint8_t codeType;
    uint32_t totalInstruction = 0;

    switch (registerCount) {
        case 3:
            codeType = 1;
            break;
        case 2:
            codeType = 2;
            break;
        case 0:
            codeType = 3;
            break;
        default:
            throw std::exception("Unknown instruction type");

    }

    std::string space_delimiter = " ";
    std::vector<std::string> words{};

    size_t pos = 0;
    while ((pos = s.find(space_delimiter)) != std::string::npos) { // split expression with whitespace
        words.push_back(s.substr(0, pos));
        s.erase(0, pos + space_delimiter.length());
    }

    std::string instructionString = words[0]; // store instruction

    switch(codeType){
        case 1: { // R Type instructions
            std::cout << "R TYPE " << std::endl;

            std::string rsString = words[1];
            std::string rtString = words[2];
            std::string rdString = words[3];

            rsString.erase(std::remove(rsString.begin(), rsString.end(), '$'), rsString.end());
            rsString.erase(std::remove(rsString.begin(), rsString.end(), ','), rsString.end());
            rtString.erase(std::remove(rtString.begin(), rtString.end(), '$'), rtString.end());
            rtString.erase(std::remove(rtString.begin(), rtString.end(), ','), rtString.end());
            rdString.erase(std::remove(rdString.begin(), rdString.end(), '$'), rdString.end());

            uint32_t rs = std::stoi(rsString); // store rs
            uint32_t rt = std::stoi(rtString); // store rt
            uint32_t rd = std::stoi(rdString); // store rd

            if ((rs > 31) || (rt > 31) || (rd > 31)) {
                throw std::exception("Invalid Register");
            } else { // all R type instructions. However, sll and srl is moved into I type instruction.
                if (instructionString == "add") totalInstruction = Mnemonic::_add;
                else if (instructionString == "addu") totalInstruction = Mnemonic::_addu;
                else if (instructionString == "and") totalInstruction = Mnemonic::_and;
                else if (instructionString == "nor") totalInstruction = Mnemonic::_nor;
                else if (instructionString == "or") totalInstruction = Mnemonic::_or;
                else if (instructionString == "slt") totalInstruction = Mnemonic::_slt;
                else if (instructionString == "sltu") totalInstruction = Mnemonic::_sltu;
                else if (instructionString == "sub") totalInstruction = Mnemonic::_sub;
                else if (instructionString == "subu") totalInstruction = Mnemonic::_subu;
                else if (instructionString == "jr") totalInstruction = Mnemonic::_jr;
            }

            rs = rs << 21;
            rt = rt << 16;
            rd = rd << 11;

            totalInstruction = totalInstruction | rs;
            totalInstruction = totalInstruction | rt;
            totalInstruction = totalInstruction | rd;

            return totalInstruction;
        }
        case 2:{
            std::cout << "I TYPE " << std::endl;

            std::string rsString = words[1];
            std::string rtString = words[2];

            rsString.erase(std::remove(rsString.begin(), rsString.end(), '$'), rsString.end());
            rsString.erase(std::remove(rsString.begin(), rsString.end(), ','), rsString.end());
            rtString.erase(std::remove(rtString.begin(), rtString.end(), '$'), rtString.end());
            rtString.erase(std::remove(rtString.begin(), rtString.end(), ','), rtString.end());

            uint32_t rs = std::stoi(rsString); // store rs
            uint32_t rt = std::stoi(rtString); // store rt
            uint16_t imm = std::stoi(words[3]); // store imm

            if ((rs > 31) || (rt > 31)) { // not going to detect imm is overflowing or not
                throw std::exception("Invalid Register");
            } else{ // all I type instructions. This contains sll and srl instruction for ease of use.
                if (instructionString == "addi") totalInstruction = Mnemonic::_addi;
                else if (instructionString == "addiu") totalInstruction = Mnemonic::_addiu;
                else if (instructionString == "andi") totalInstruction = Mnemonic::_andi;
                else if (instructionString == "ori") totalInstruction = Mnemonic::_ori;
                else if (instructionString == "slti") totalInstruction = Mnemonic::_slti;
                else if (instructionString == "sltiu") totalInstruction = Mnemonic::_sltiu;
                else if (instructionString == "beq") totalInstruction = Mnemonic::_beq;
                else if (instructionString == "bne") totalInstruction = Mnemonic::_bne;
                else if (instructionString == "sll") totalInstruction = Mnemonic::_sll; // was R type
                else if (instructionString == "srl") totalInstruction = Mnemonic::_srl; // was R type
            }

            rs = rs << 21;
            rt = rt << 16;

            totalInstruction = totalInstruction | rs;
            totalInstruction = totalInstruction | rt;
            totalInstruction = totalInstruction | imm;

            return totalInstruction;
        }
        case 3:{ // j type
            std::cout << "J TYPE " << std::endl;

            uint32_t address = std::stoi(words[1]); // store address
            if (instructionString == "j") totalInstruction = Mnemonic::_j;
            else if (instructionString == "jal") totalInstruction = Mnemonic::_jal;
            totalInstruction = totalInstruction | address;

            return totalInstruction;
        }
    }
    throw std::exception("Invalid instruction type");
}
//
// @file : Memory.h
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : A file that defines all attributes and member functions for class Memory
// @date: 2022-03-08

#ifndef MIPSIM_MEMORY_H
#define MIPSIM_MEMORY_H


#include <cstdint>
#include <cstdlib>


class Memory {
private:
    uint32_t* memoryCells;
    uint32_t curCellIndex;
public:
    Memory(uint32_t);
    uint32_t* readAddress(uint32_t);
    void dumpValue(uint32_t, uint32_t);
    void addCell(uint32_t);
};


#endif //MIPSIM_MEMORY_H

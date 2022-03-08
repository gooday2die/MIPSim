//
// @file : Memory.cpp
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : A file that implements all member functions for class Register
// @date: 2022-03-08

#include "Memory.h"

/**
 * A constructor member function for class Memory
 * For example, if the total byte count is 32 byte, the count would be 8
 * @param cellCount the total 4byte count for the total Memory
 */
Memory::Memory(uint32_t cellCount) {
    this->curCellIndex = 0;
    this->memoryCells = (uint32_t*)malloc(sizeof(uint32_t) * cellCount); // generate cells
    for (uint32_t i = 0 ; i < 32 ; i ++) this->memoryCells[i] = 0; // clear them with 0s
}

/**
 * A member function that reads a specific index from memory
 * @param index the index of memory
 * @return uint32_t pointer type of the memory
 */
uint32_t* Memory::readAddress(uint32_t index) {
    return this->memoryCells + index;
}

void Memory::dumpValue(uint32_t index, uint32_t machineCode){
    this->memoryCells[index] = machineCode;
}

void Memory::addCell(uint32_t value){
    this->memoryCells[curCellIndex] = value;
    this->curCellIndex++;

}
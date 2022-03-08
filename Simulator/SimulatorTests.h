//
// @file : SimulatorTests.h
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : A file that defines all attributes and member functions for class SimulatorTests
// @date: 2022-03-07

#ifndef MIPSIM_SIMULATORTESTS_H
#define MIPSIM_SIMULATORTESTS_H
#pragma once

#include "Simulator.h"

class SimulatorTests {
private:
    Simulator s = Simulator();
public:
    void test_add_addi();
    void test_addu_addiu();
    void test_and_andi();
    //void test_or_nor();
    //void test_slt_slti();
    //void test_sltu_sltiu();
};


#endif //MIPSIM_SIMULATORTESTS_H

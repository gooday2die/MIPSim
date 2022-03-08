//
// @file : Register.cpp
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : A file that implements all member functions for class Register
// @date: 2022-03-07

#include "Register.h"

/**
 * A constructor member function for Register
 * @param argValue int value to set default
 */
Register::Register(uint32_t argValue){
    this->value = argValue;
}

/**
 * A member function for getting variable value
 * @return int type value of this register's value
 */
uint32_t Register::getValue() {
    return this->value;
}

/**
 * A member function for setting value to a variable
 * @param argValue int type value to set as this register
 */
void Register::setValue(uint32_t argValue){
    this->value = argValue;
}
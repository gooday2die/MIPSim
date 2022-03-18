//
// @file : Translator.cpp
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : A file that implements all member functions for class Translator
//

#include "Translator.h"

/**
 * A constructor member function for class Translator.
 * This member function initializes this class by inserting all values into maps for future translation.
 */
Translator::Translator() {
    this->registerMnemonics.insert(pair<string, uint8_t>("zero",0));
    this->registerMnemonics.insert(pair<string, uint8_t>("at", 1));
    this->registerMnemonics.insert(pair<string, uint8_t>("v0", 2));
    this->registerMnemonics.insert(pair<string, uint8_t>("v1", 3));
    this->registerMnemonics.insert(pair<string, uint8_t>("a0", 4));
    this->registerMnemonics.insert(pair<string, uint8_t>("a1", 5));
    this->registerMnemonics.insert(pair<string, uint8_t>("a2", 6));
    this->registerMnemonics.insert(pair<string, uint8_t>("a3", 7));
    this->registerMnemonics.insert(pair<string, uint8_t>("t0", 8));
    this->registerMnemonics.insert(pair<string, uint8_t>("t1", 9));
    this->registerMnemonics.insert(pair<string, uint8_t>("t2", 10));
    this->registerMnemonics.insert(pair<string, uint8_t>("t3", 11));
    this->registerMnemonics.insert(pair<string, uint8_t>("t4", 12));
    this->registerMnemonics.insert(pair<string, uint8_t>("t5", 13));
    this->registerMnemonics.insert(pair<string, uint8_t>("t6", 14));
    this->registerMnemonics.insert(pair<string, uint8_t>("t7", 15));
    this->registerMnemonics.insert(pair<string, uint8_t>("s0", 16));
    this->registerMnemonics.insert(pair<string, uint8_t>("s1", 17));
    this->registerMnemonics.insert(pair<string, uint8_t>("s2", 18));
    this->registerMnemonics.insert(pair<string, uint8_t>("s3", 19));
    this->registerMnemonics.insert(pair<string, uint8_t>("s4", 20));
    this->registerMnemonics.insert(pair<string, uint8_t>("s5", 21));
    this->registerMnemonics.insert(pair<string, uint8_t>("s6", 22));
    this->registerMnemonics.insert(pair<string, uint8_t>("s7", 23));
    this->registerMnemonics.insert(pair<string, uint8_t>("t8", 24));
    this->registerMnemonics.insert(pair<string, uint8_t>("t9", 25));
    this->registerMnemonics.insert(pair<string, uint8_t>("k0", 26));
    this->registerMnemonics.insert(pair<string, uint8_t>("k1", 27));
    this->registerMnemonics.insert(pair<string, uint8_t>("gp", 28));
    this->registerMnemonics.insert(pair<string, uint8_t>("sp", 29));
    this->registerMnemonics.insert(pair<string, uint8_t>("fp", 30));
    this->registerMnemonics.insert(pair<string, uint8_t>("ra", 31));
}

/**
 * A member function for class Translator that translates given register string into register index value
 * @param registerString the string that represents register's index or mnemonic if the register.
 * @return returns uint8_t type that represents register's index.
 */
uint8_t Translator::translateRegister(const string& registerString) {
    string copied;
    uint8_t registerIndex;
    copied = regex_replace(registerString, regex("$"), "");
    try{
        registerIndex = stoi(copied);
    } catch (const std::range_error& ex){
        try{
            registerIndex = this->registerMnemonics.at(copied);
        } catch (const range_error& ex){
            throw TranslatorExceptions::cannotFindRegisterIndexException();
        }
    }
    return registerIndex;
}
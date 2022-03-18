//
// @file : Label.
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : 
//

#ifndef MIPSIM_LABEL_H
#define MIPSIM_LABEL_H
#pragma once

#include <string>

using namespace std;
class Label {
private:
    string labelName;
    uint32_t address = 0;
public:
    explicit Label(const string&);
    void setAddress(uint32_t);
    uint32_t getAddress();
    string getLabelName();
};


#endif //MIPSIM_LABEL_H

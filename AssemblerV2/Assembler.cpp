//
// @file : Assembler.
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : 
// @date: 2022-03-15

#include "Assembler.h"


Assembler::Assembler(string argFileName) {
    this->fileName = move(argFileName);
    this->fileReader = new FileReader(this->fileName);
    this->allExpressions = this->fileReader->getAllExpressions();

    this->parseSections();
    if (this->allErrors.empty()) this->printErrors();
}

void Assembler::parseSections() {
    uint32_t curPointer = 0 ;
    uint32_t dataSectionStart = 0;
    uint32_t dataSectionEnd = 0;
    uint32_t textSectionStart = 0;
    uint32_t textSectionEnd = 0;

    // 0 : is not a section, 1 : text section, 2 : data section
    uint8_t currentSectionType = 0;

    for (auto const& expression : this->allExpressions){
        if (expression.second.find(".text") != string::npos){
            if(currentSectionType == 0){
                currentSectionType = 1;
                textSectionStart = !textSectionStart ? 0 : curPointer - 1;
            } else if (currentSectionType == 1){
                this->allErrors.emplace_back(AssemblerError("Multiple .text sections found", expression.second, curPointer));
            } else{
                dataSectionEnd = curPointer;
                textSectionStart = curPointer;
            }
        }

        else if (expression.second.find(".data") != string::npos){
            if(currentSectionType == 0){
                currentSectionType = 2;
                dataSectionStart = !dataSectionStart ? 0 : curPointer - 1;
            } else if (currentSectionType == 2){
                this->allErrors.emplace_back(AssemblerError("Multiple .data sections found", expression.second, curPointer));
            } else{
                textSectionEnd = curPointer;
                dataSectionStart = curPointer;
            }
        }
        curPointer++;
        std::cout << expression.first << " : " << expression.second << std::endl;
    }

    if(textSectionEnd == 0) textSectionEnd = curPointer;
    else if(dataSectionEnd == 0) dataSectionEnd = curPointer;

    cout << "TEXT : " << to_string(textSectionStart) << " ~ " << to_string(textSectionEnd) << std::endl;
    cout << "DATA : " << to_string(dataSectionStart) << " ~ " << to_string(dataSectionEnd) << std::endl;
}

void Assembler::printErrors() {
    for (auto x : this->allErrors){
        x.print();
    }
}
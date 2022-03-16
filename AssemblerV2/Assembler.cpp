//
// @file : Assembler.
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : 
// @date: 2022-03-15

#include "Assembler.h"

/**
 * A constructor member function for class Assembler
 * @param argFileName the string object that represents file name
 */
Assembler::Assembler(string argFileName) {
    this->fileName = move(argFileName);
    this->fileReader = new FileReader(this->fileName);
    this->allExpressions = this->fileReader->getAllExpressions();

    this->parseSections();
    if (!this->allErrors.empty()) this->printErrors();
}

/**
 * A member function for class Assembler
 * @return returns uint16_t type that represents data section count in MSB 8 bits, text section count in LSB 8 bits
 */
uint16_t Assembler::scanSections() {
    uint8_t textSectionCount = 0;
    uint8_t dataSectionCount = 0;
    for (auto const& x : this->allExpressions){
        textSectionCount = textSectionCount + (x.second.getExpressionString().find(".text") != string::npos);
        dataSectionCount = dataSectionCount + (x.second.getExpressionString().find(".data") != string::npos);
    }

    uint16_t returnValue = 0x0000;
    returnValue = returnValue | textSectionCount;
    returnValue = returnValue | ((dataSectionCount << 8) & 0xFF00);

    return returnValue;
}

/**
 * A member function that parses .text and .data sections.
 * This will set generate textSection and dataSection attributes automatically.
 */
void Assembler::parseSections() {
    vector<Expression> dataSectionExpressions;
    vector<Expression> textSectionExpressions;
    uint16_t sectionCounts = this->scanSections();
    uint8_t textSectionCount = sectionCounts & 0xFF;
    uint8_t dataSectionCount = (sectionCounts >> 8) & 0xFF;


    /// Current section type defaults to 1 if there were no text section that was manually declared.
    /// However, if text section was declared manually current section type defaults to 0 since it would not be regarded
    /// as text section.
    uint8_t currentSectionType = textSectionCount != 0 ? 0 : 1; // type 1: text, type 2: data

    uint32_t curPointer = 0;
    for (auto const& x : this->allExpressions){
        string expressionString = x.second.getExpressionString();
        if(expressionString.find(".text") != string::npos) currentSectionType = 1; // set current section types
        else if(expressionString.find(".data") != string::npos) currentSectionType = 2;

        if (currentSectionType == 1){
            textSectionExpressions.push_back(x.second);
        }
        else if (currentSectionType == 2){
            dataSectionExpressions.push_back(x.second);
        } else{
            if (!expressionString.empty())
            this->allErrors.emplace_back(AssemblerError("Expression without section was found.", expressionString, curPointer));
        }
        std::cout << x.first << " : " <<x.second.getExpressionString() << std::endl;
        curPointer++;
    }

    this->dataSection = new Section(dataSectionExpressions, 2);
    this->textSection = new Section(textSectionExpressions, 1);

    this->dataSection->printSection();
    this->textSection->printSection();

}

/**
 * A member function that prints out errors
 */
void Assembler::printErrors() {
    for (auto x : this->allErrors){
        x.print();
    }
}
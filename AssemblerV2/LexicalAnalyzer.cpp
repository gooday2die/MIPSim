//
// @file : LexicalAnalyzer.
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : 
// @date: 2022-03-16

#include "LexicalAnalyzer.h"

bool LexicalAnalyzer::isSectionToken(const std::string& argumentString) {
    if((argumentString == ".text")
        || (argumentString == ".data")) return true;
    return false;
}

bool LexicalAnalyzer::isLabelToken(const std::string& argumentString){
    if (std::count(argumentString.begin(), argumentString.end(), ':') == 1) return true;
    else return false;
}

bool LexicalAnalyzer::isImmediateToken(const std::string& argumentString) {
    try{
        std::stoi(argumentString);
        return true;
    } catch(std::exception const& ex){
        return false;
    }
}

bool LexicalAnalyzer::isRegisterToken(const std::string& argumentString) {
    std::string copiedString = argumentString;
    try{
        copiedString.erase(std::remove(copiedString.begin(), copiedString.end(), '$'), copiedString.end());
        uint8_t converted = std::stoi(copiedString);
        if ((converted > 0) && (converted < 31)) return true;
        else return false;
    } catch (const std::exception& ex){
        if ((copiedString == "&zero")
           ||(copiedString == "&at")
           ||(copiedString == "&v0")
           ||(copiedString == "&v1")
           ||(copiedString == "&a0")
           ||(copiedString == "&a1")
           ||(copiedString == "&a2")
           ||(copiedString == "&a3")
           ||(copiedString == "&t0")
           ||(copiedString == "&t1")
           ||(copiedString == "&t2")
           ||(copiedString == "&t3")
           ||(copiedString == "&t4")
           ||(copiedString == "&t5")
           ||(copiedString == "&t6")
           ||(copiedString == "&t7")
           ||(copiedString == "&s0")
           ||(copiedString == "&s1")
           ||(copiedString == "&s2")
           ||(copiedString == "&s3")
           ||(copiedString == "&s4")
           ||(copiedString == "&s5")
           ||(copiedString == "&s6")
           ||(copiedString == "&s7")
           ||(copiedString == "&t8")
           ||(copiedString == "&t9")
           ||(copiedString == "&k0")
           ||(copiedString == "&k1")
           ||(copiedString == "&gp")
           ||(copiedString == "&sp")
           ||(copiedString == "&fp")
           ||(copiedString == "&ra")) return true;
        else return false;
    }
}

std::string LexicalAnalyzer::getLabelName(const std::string& argumentString) {
    const char* line = argumentString.c_str();
    uint16_t curPos = 0;
    while(line[curPos] != '\0'){
        if(line[curPos] == ':') return argumentString.substr(0, curPos);
        else curPos++;
    }
    return "";
}

std::string LexicalAnalyzer::getSectionName(const std::string& argumentString) {
    const char* line = argumentString.c_str();
    uint16_t curPos = 0;
    while(line[curPos] != '\0'){
        if(line[curPos] == '.')
            return argumentString.substr(curPos + 1, argumentString.size());
        else curPos++;
    }
    return "";
}

void LexicalAnalyzer::analyze(const std::string& expressionString) {
    std::string copied = expressionString;
    if (isSectionToken(copied)) std::cout << "SECTION TOKEN :" << getSectionName(copied) << std::endl;
    else if (isLabelToken(copied)) std::cout << "LABEL TOKEN : " << getLabelName(copied) << std::endl;
    std::cout << copied << std::endl;
}
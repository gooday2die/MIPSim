//
// @file : Assembler.cpp
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

    this->lexicalAnalyzer = new LexicalAnalyzer(this->allExpressions);
    this->syntaxAnalyzer = new SyntaxAnalyzer();
    this->semanticAnalyzer = new SemanticAnalyzer();

    this->assemble();
}

/**
 * A member function for class Assembler that checks expression's grammar using lexical analysis, syntax analysis
 * and semantic analysis. This member function throws exceptions when it finds out a syntax or semantic error.
 * @param expressionString the string object that represents current expression.
 */
void Assembler::checkExpressionGrammar(const string& expressionString){
    pair<string, queue<Tokens>> result = this->lexicalAnalyzer->analyze(expressionString);
    this->syntaxAnalyzer->analyze(result);
    this->semanticAnalyzer->analyze(result);
}

/**
 * A member function for class Assembler that checks all expression's grammar and prints out errors if they have one.
 * This checks each expression's syntax errors and semantic errors. If any errors occur, the errors are stored in
 * totalErrorCount for future use.
 */
void Assembler::checkGrammar() {
    uint32_t i = 0;
    uint32_t expressionCount = 0;
    for(auto const& x : this->allExpressions){
        if((x.second.getExpressionString() != " ") || (x.second.getExpressionString().empty())){
            try {
                this->checkExpressionGrammar(x.second.getExpressionString());
            } catch(const ExpressionExceptions::unknownInstructionMnemonicException& ex){
                const string& errorExpression = this->allExpressions.find(i)->second.getExpressionString();
                cout << ERROR_TAG << " Unknown mnemonic expression was found  ";
                cout << "@ln " << to_string(i) << " -> " << ERROR_EXPRESSION << std::endl;
                this->totalErrorCount++;
            } catch (const ExpressionExceptions::invalidArgumentException& ex){
                const string& errorExpression = this->allExpressions.find(i)->second.getExpressionString();
                cout << ERROR_TAG << " Invalid argument found  ";
                cout << "@ln " << to_string(i) << " -> " << ERROR_EXPRESSION << std::endl;
                this->totalErrorCount++;
            } catch (const ExpressionExceptions::unknownTokenException& ex){
                const string& errorExpression = this->allExpressions.find(i)->second.getExpressionString();
                cout << ERROR_TAG << " Unknown token was found  ";
                cout << "@ln " << to_string(i) << " -> " << ERROR_EXPRESSION << std::endl;
                this->totalErrorCount++;
            } catch (const ExpressionExceptions::bareImmediateValueException& ex){
                const string& errorExpression = this->allExpressions.find(i)->second.getExpressionString();
                cout << ERROR_TAG << " Immediate value without expression was found  ";
                cout << "@ln " << to_string(i) << " -> " << ERROR_EXPRESSION << std::endl;
                this->totalErrorCount++;
            } catch (const ExpressionExceptions::bareRegisterException& ex){
                const string& errorExpression = this->allExpressions.find(i)->second.getExpressionString();
                cout << ERROR_TAG << " Register without expression was found  ";
                cout << "@ln " << to_string(i) << " -> " << ERROR_EXPRESSION << std::endl;
                this->totalErrorCount++;
            } catch (const ExpressionExceptions::bareLabelException& ex){
                const string& errorExpression = this->allExpressions.find(i)->second.getExpressionString();
                cout << ERROR_TAG << " Label value without expression was found  ";
                cout << "@ln " << to_string(i) << " -> " << ERROR_EXPRESSION << std::endl;
                this->totalErrorCount++;
            } catch (const BranchExceptions::duplicateNameException& ex){
                const string& errorExpression = this->allExpressions.find(i)->second.getExpressionString();
                cout << ERROR_TAG << " Duplicate label declaration was found  ";
                cout << "@ln " << to_string(i) << " -> " << ERROR_EXPRESSION << std::endl;
                this->totalErrorCount++;
            }
            expressionCount++;
            i++;
        }
    }
}

/**
 * A member function for class Assembler that assembles current code into machine code.
 * This member function does the following things.
 * 1. Perform Lexical analysis and parse out tokens.
 * 2. Perform Syntax analysis and checks if syntax was correct.
 */
void Assembler::assemble() {
    cout << "Assembling..." << endl;
    this->checkGrammar();

    if(this->totalErrorCount > 0){
        cout << ASSEMBLE_FAILED << endl;
        cout << "Found " << to_string(this->totalErrorCount) << " error(s)" << endl;
        exit(0);
    } else{
        cout << ASSEMBLE_SUCCESS << endl;
    }
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
            //if (!expressionString.empty())
            //this->allErrors.emplace_back(AssemblerError("Expression without section was found.", expressionString, curPointer));
        }
        cout << x.first << " : " <<x.second.getExpressionString() << endl;
        curPointer++;
    }

    this->dataSection = new Section(dataSectionExpressions, 2);
    this->textSection = new Section(textSectionExpressions, 1);

    this->dataSection->printSection();
    this->textSection->printSection();
}

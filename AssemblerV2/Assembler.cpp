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
    this->allExpressionStrings = this->fileReader->getAllExpressions();

    this->lexicalAnalyzer = new LexicalAnalyzer(this->allExpressionStrings);
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
    uint32_t lineCount = 0;
    uint32_t expressionCount = 0;
    for(auto const& x : this->allExpressionStrings){
        if((x.second != " ") || (x.second.empty())){
            try {
                this->checkExpressionGrammar(x.second);
            } catch(const ExpressionExceptions::unknownInstructionMnemonicException& ex){
                const string& errorExpression = this->allExpressionStrings.find(lineCount)->second;
                cout << ERROR_TAG << " Unknown mnemonic expression was found  ";
                cout << "@ln " << to_string(lineCount) << " -> " << ERROR_EXPRESSION << std::endl;
                this->totalErrorCount++;
            } catch (const ExpressionExceptions::invalidArgumentException& ex){
                const string& errorExpression = this->allExpressionStrings.find(lineCount)->second;
                cout << ERROR_TAG << " Invalid argument found  ";
                cout << "@ln " << to_string(lineCount) << " -> " << ERROR_EXPRESSION << std::endl;
                this->totalErrorCount++;
            } catch (const ExpressionExceptions::unknownTokenException& ex){
                const string& errorExpression = this->allExpressionStrings.find(lineCount)->second;
                cout << ERROR_TAG << " Unknown token was found  ";
                cout << "@ln " << to_string(lineCount) << " -> " << ERROR_EXPRESSION << std::endl;
                this->totalErrorCount++;
            } catch (const ExpressionExceptions::bareImmediateValueException& ex){
                const string& errorExpression = this->allExpressionStrings.find(lineCount)->second;
                cout << ERROR_TAG << " Immediate value without expression was found  ";
                cout << "@ln " << to_string(lineCount) << " -> " << ERROR_EXPRESSION << std::endl;
                this->totalErrorCount++;
            } catch (const ExpressionExceptions::bareRegisterException& ex){
                const string& errorExpression = this->allExpressionStrings.find(lineCount)->second;
                cout << ERROR_TAG << " Register without expression was found  ";
                cout << "@ln " << to_string(lineCount) << " -> " << ERROR_EXPRESSION << std::endl;
                this->totalErrorCount++;
            } catch (const ExpressionExceptions::bareLabelException& ex){
                const string& errorExpression = this->allExpressionStrings.find(lineCount)->second;
                cout << ERROR_TAG << " Label value without expression was found  ";
                cout << "@ln " << to_string(lineCount) << " -> " << ERROR_EXPRESSION << std::endl;
                this->totalErrorCount++;
            } catch (const ExpressionExceptions::duplicateLabelNameException& ex){
                const string& errorExpression = this->allExpressionStrings.find(lineCount)->second;
                cout << ERROR_TAG << " Duplicate label declaration was found  ";
                cout << "@ln " << to_string(lineCount) << " -> " << ERROR_EXPRESSION << std::endl;
                this->totalErrorCount++;
            } catch (const ExpressionExceptions::tokenInWrongSection& ex){
                const string& errorExpression = this->allExpressionStrings.find(lineCount)->second;
                cout << ERROR_TAG << " Token was found in wrong code section  ";
                cout << "@ln " << to_string(lineCount) << " -> " << ERROR_EXPRESSION << std::endl;
                this->totalErrorCount++;
            } catch (const ExpressionExceptions::unknownPseudoInstructionMnemonicException& ex){
                const string& errorExpression = this->allExpressionStrings.find(lineCount)->second;
                cout << ERROR_TAG << " Unknown pseudo-instruction was found  ";
                cout << "@ln " << to_string(lineCount) << " -> " << ERROR_EXPRESSION << std::endl;
                this->totalErrorCount++;
            }
            expressionCount++;
        }
        lineCount++;
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

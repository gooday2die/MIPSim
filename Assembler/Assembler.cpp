//
// @file : Assembler.cpp
// @author : Gooday2die (Isu Kim)
// Contacts : edina00@naver.com
// @brief : A file that implements all member functions for class Assembler
//

#include "Assembler.h"

/**
 * A constructor member function for class Assembler
 * @param argFileName the string object that represents file name
 */
Assembler::Assembler(string argFileName, uint32_t* argRegisters, uint32_t* argPc) {
    cout << "===== MIPSim Assembler Version : " << MIPSIM_VERSION << " by Gooday2die =====" << endl;
    this->fileName = move(argFileName);
    this->fileReader = new FileReader(this->fileName);
    this->allExpressionStrings = this->fileReader->getAllExpressions();

    this->lexicalAnalyzer = new LexicalAnalyzer(this->allExpressionStrings);
    this->syntaxAnalyzer = new SyntaxAnalyzer();
    this->semanticAnalyzer = new SemanticAnalyzer();
    this->translator = new Translator(argRegisters, argPc);

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
 * A member function for class Assembler that translates all expression into machine codes.
 * When it is done translating, this will automatically load machine codes into allMachineCodes attribute.
 */
void Assembler::translate() {
    vector<Expression> allExpressions;
    for (auto const& x: this->allExpressionStrings){
        string space_delimiter = " ";
        vector<string> words{};
        string copied = x.second;

        size_t pos = 0;
        while ((pos = copied.find(space_delimiter)) != string::npos) { // split expression with whitespace
            words.push_back(copied.substr(0, pos));
            copied.erase(0, pos + space_delimiter.length());
        }

        queue<Tokens> tokenQueue = this->lexicalAnalyzer->analyze(x.second).second;
        this->translator->scanLabelAddresses(tokenQueue.front(), words[0]);
    }

    uint32_t lineCount = 0;
    for (auto const& x: this->allExpressionStrings){
        pair<string, queue<Tokens>> tokenInfo = this->lexicalAnalyzer->analyze(x.second);
        vector<Expression> results;
        try {
             results = this->translator->translate(tokenInfo.second, x.second);
             for (Expression y : results)
                 allExpressions.emplace_back(y);
        } catch (const TranslatorExceptions::cannotFindRegisterIndexException& ex){
            const string& errorExpression = this->allExpressionStrings.find(lineCount)->second;
            cout << TRANSLATOR_ERROR_TAG << " Cannot find register ";
            cout << "@ln " << to_string(lineCount) << " -> " << ERROR_EXPRESSION << std::endl;
            this->totalErrorCount++;
        } catch (const TranslatorExceptions::cannotTranslateImmediateException& ex){
            const string& errorExpression = this->allExpressionStrings.find(lineCount)->second;
            cout << TRANSLATOR_ERROR_TAG << " Cannot translate immediate value ";
            cout << "@ln " << to_string(lineCount) << " -> " << ERROR_EXPRESSION << std::endl;
            this->totalErrorCount++;
        } catch (const TranslatorExceptions::cannotFindInstructionMnemonicException& ex){
            const string& errorExpression = this->allExpressionStrings.find(lineCount)->second;
            cout << TRANSLATOR_ERROR_TAG << " Cannot find instruction mnemonic ";
            cout << "@ln " << to_string(lineCount) << " -> " << ERROR_EXPRESSION << std::endl;
            this->totalErrorCount++;
        } catch (const TranslatorExceptions::unexpectedInstructionArgumentTokenException& ex){
            const string& errorExpression = this->allExpressionStrings.find(lineCount)->second;
            cout << TRANSLATOR_ERROR_TAG << " Unexpected instruction argument token ";
            cout << "@ln " << to_string(lineCount) << " -> " << ERROR_EXPRESSION << std::endl;
            this->totalErrorCount++;
        } catch (const TranslatorExceptions::unexpectedInstructionTokenTypeException& ex){
            const string& errorExpression = this->allExpressionStrings.find(lineCount)->second;
            cout << TRANSLATOR_ERROR_TAG << " Unexpected instruction token type ";
            cout << "@ln " << to_string(lineCount) << " -> " << ERROR_EXPRESSION << std::endl;
            this->totalErrorCount++;
        } catch (const TranslatorExceptions::cannotFindLabelNameException& ex){
            const string& errorExpression = this->allExpressionStrings.find(lineCount)->second;
            cout << TRANSLATOR_ERROR_TAG << " Cannot find label name ";
            cout << "@ln " << to_string(lineCount) << " -> " << ERROR_EXPRESSION << std::endl;
            this->totalErrorCount++;
        }
        lineCount++;
    }

    uint32_t curPos = 0;
    this->textSectionExpressions = allExpressions;
    this->translator->printLabels();

    this->totalExpressionCount = allExpressions.size();
    this->totalLabelCount = this->translator->getLabelCount();
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
            } catch(const GrammarExceptions::unknownInstructionMnemonicException& ex){
                const string& errorExpression = this->allExpressionStrings.find(lineCount)->second;
                cout << ERROR_TAG << " Unknown mnemonic expression was found  ";
                cout << "@ln " << to_string(lineCount) << " -> " << ERROR_EXPRESSION << std::endl;
                this->totalErrorCount++;
            } catch (const GrammarExceptions::invalidArgumentException& ex){
                const string& errorExpression = this->allExpressionStrings.find(lineCount)->second;
                cout << ERROR_TAG << " Invalid argument found  ";
                cout << "@ln " << to_string(lineCount) << " -> " << ERROR_EXPRESSION << std::endl;
                this->totalErrorCount++;
            } catch (const GrammarExceptions::unknownTokenException& ex){
                const string& errorExpression = this->allExpressionStrings.find(lineCount)->second;
                cout << ERROR_TAG << " Unknown token was found  ";
                cout << "@ln " << to_string(lineCount) << " -> " << ERROR_EXPRESSION << std::endl;
                this->totalErrorCount++;
            } catch (const GrammarExceptions::bareImmediateValueException& ex){
                const string& errorExpression = this->allExpressionStrings.find(lineCount)->second;
                cout << ERROR_TAG << " Immediate value without expression was found  ";
                cout << "@ln " << to_string(lineCount) << " -> " << ERROR_EXPRESSION << std::endl;
                this->totalErrorCount++;
            } catch (const GrammarExceptions::bareRegisterException& ex){
                const string& errorExpression = this->allExpressionStrings.find(lineCount)->second;
                cout << ERROR_TAG << " Register without expression was found  ";
                cout << "@ln " << to_string(lineCount) << " -> " << ERROR_EXPRESSION << std::endl;
                this->totalErrorCount++;
            } catch (const GrammarExceptions::bareLabelException& ex){
                const string& errorExpression = this->allExpressionStrings.find(lineCount)->second;
                cout << ERROR_TAG << " Label value without expression was found  ";
                cout << "@ln " << to_string(lineCount) << " -> " << ERROR_EXPRESSION << std::endl;
                this->totalErrorCount++;
            } catch (const GrammarExceptions::duplicateLabelNameException& ex){
                const string& errorExpression = this->allExpressionStrings.find(lineCount)->second;
                cout << ERROR_TAG << " Duplicate label declaration was found  ";
                cout << "@ln " << to_string(lineCount) << " -> " << ERROR_EXPRESSION << std::endl;
                this->totalErrorCount++;
            } catch (const GrammarExceptions::tokenInWrongSection& ex){
                const string& errorExpression = this->allExpressionStrings.find(lineCount)->second;
                cout << ERROR_TAG << " Token was found in wrong code section  ";
                cout << "@ln " << to_string(lineCount) << " -> " << ERROR_EXPRESSION << std::endl;
                this->totalErrorCount++;
            } catch (const GrammarExceptions::unknownPseudoInstructionMnemonicException& ex){
                const string& errorExpression = this->allExpressionStrings.find(lineCount)->second;
                cout << ERROR_TAG << " Unknown pseudo-instruction was found  ";
                cout << "@ln " << to_string(lineCount) << " -> " << ERROR_EXPRESSION << std::endl;
                this->totalErrorCount++;
            } catch (const GrammarExceptions::bareStringException& ex){
                const string& errorExpression = this->allExpressionStrings.find(lineCount)->second;
                cout << ERROR_TAG << " String without expression was found  ";
                cout << "@ln " << to_string(lineCount) << " -> " << ERROR_EXPRESSION << std::endl;
                this->totalErrorCount++;
            } catch (const GrammarExceptions::bareLabelDefinitionException& ex){
                const string& errorExpression = this->allExpressionStrings.find(lineCount)->second;
                cout << ERROR_TAG << " Label definition was invalid  ";
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
 * 3. Perform Semantic analysis and check if it was grammatically correct.
 * 4. Translate into machine codes.
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
        this->translate();
        cout << "Assembled " << to_string(this->totalExpressionCount) << " expression(s)" << endl;
        cout << "Generated " << to_string(this->totalLabelCount) << " label(s)\n" << endl;
    }
}

/**
 * A member function that gets all text section expressions
 * @return returns vector of Expression objects that has all expressions.
 */
vector<Expression> Assembler::getTextSectionExpressions(){
    return this->textSectionExpressions;
}
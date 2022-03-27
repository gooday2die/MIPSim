cmake_minimum_required(VERSION 3.21)
project(MIPSim2)

set(CMAKE_CXX_STANDARD 14)

add_executable(MIPSim2 main.cpp Utils/Instruction.cpp Utils/Instruction.h Utils/Expression.cpp Utils/Expression.h MIPSim.cpp MIPSim.h Assembler/Assembler.cpp Assembler/Assembler.h
        Assembler/Errors.h Assembler/FileReader.h Assembler/FileReader.cpp Assembler/LexicalAnalyzer.h Assembler/LexicalAnalyzer.cpp Assembler/Messages.h Assembler/SemanticAnalyzer.h
        Assembler/SemanticAnalyzer.cpp Assembler/Token.h Assembler/SyntaxAnalyzer.h/ Assembler/SyntaxAnalyzer.cpp Assembler/Translator.h Assembler/Translator.cpp)

cmake_minimum_required(VERSION 3.21)
project(MIPSim)

set(CMAKE_CXX_STANDARD 14)

add_executable(MIPSim main.cpp Simulator/RegisterHandler.cpp Simulator/RegisterHandler.h Simulator/Instructions.cpp Simulator/Instructions.h Simulator/Simulator.cpp Simulator/Simulator.h Simulator/MachineCodeSimulator.cpp Simulator/MachineCodeSimulator.cpp Simulator/MachineCodeSimulator.h defines.h Assembler/Translator.cpp Assembler/Translator.h Assembler/FileReader.cpp Assembler/FileReader.h main.h Assembler/Assembler.cpp Assembler/Assembler.h Assembler/GrammarChecker.cpp Assembler/GrammarChecker.h Assembler/Expression.cpp Assembler/Expression.h Assembler/Messages.h Assembler/AssemblerErrors.h)

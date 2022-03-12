cmake_minimum_required(VERSION 3.21)
project(MIPSim)

set(CMAKE_CXX_STANDARD 14)

add_executable(MIPSim main.cpp Simulator/RegisterHandler.cpp Simulator/RegisterHandler.h Simulator/Instructions.cpp Simulator/Instructions.h Simulator/Simulator.cpp Simulator/Simulator.h Simulator/MachineCodeSimulator.cpp Simulator/MachineCodeSimulator.cpp Simulator/MachineCodeSimulator.h defines.h Parser/Translator.cpp Parser/Translator.h Parser/FileReader.cpp Parser/FileReader.h main.h Parser/Assembler.cpp Parser/Assembler.h Parser/GrammarChecker.cpp Parser/GrammarChecker.h Parser/Expression.cpp Parser/Expression.h)

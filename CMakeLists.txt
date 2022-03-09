cmake_minimum_required(VERSION 3.21)
project(MIPSim)

set(CMAKE_CXX_STANDARD 14)

add_executable(MIPSim main.cpp Simulator/RegisterHandler.cpp Simulator/RegisterHandler.h Instructions/Instructions.cpp Instructions/Instructions.h Simulator/Simulator.cpp Simulator/Simulator.h MachineCodes/MachineCodeSimulator.cpp MachineCodes/MachineCodeSimulator.cpp MachineCodes/MachineCodeSimulator.h defines.h Simulator/SimulatorTests.cpp Simulator/SimulatorTests.h Parser/Assembler.cpp Parser/Assembler.h)

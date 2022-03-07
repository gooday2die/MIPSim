cmake_minimum_required(VERSION 3.21)
project(MIPSim)

set(CMAKE_CXX_STANDARD 14)

add_executable(MIPSim main.cpp Instructions/AbstractInstructions.h Register/Register.cpp Register/Register.h Register/RegisterHandler.cpp Register/RegisterHandler.h Instructions/Instructions.cpp Instructions/Instructions.h Simulator/Simulator.cpp Simulator/Simulator.h MachineCodes/MachineCode.cpp MachineCodes/MachineCode.h MachineCodes/MachineCodeSimulator.cpp MachineCodes/MachineCodeSimulator.cpp MachineCodes/MachineCodeSimulator.h defines.h)

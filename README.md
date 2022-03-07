
# MIPSim
A MIPS assembly simulator written in C++

## Motivation
While I was suffering from lack of brilliant inspiration for new projects, I came up with this project since I had a class on MIPS assembly. 

## Features
- **Runs in Virtual Machine Code level**

Each instructions will be converted into machine codes that corresponds with MIPS assembly. `MIPSim` has built in `MachineCodeSimulator` and executes those operations.
- **OOP Style**

Each instructions are implemented as classes and its member functions. Thus modifying each instructions are easy.
## Installation
This project uses [CMake](https://cmake.org/). There is a `CMakeLists.txt` included in this project so you can easily build this project by using `cmake`

## Supported Instructions
Following instructions of MIPS assembly are currently supported with `MIPSim`. `MIPSim` is still in development phase, so there might be bugs or lack some important features.
|Instruction Name|OPCODE|FUNCT|Type|
|--|--|--|--|
|add|0x00|0x20| R  
|addi|0x08|NA| I 
|addiu|0x09|NA| I 
|addu|0x00|0x21| R 
|and|0x00|0x24| R 
|andi|0x0C|NA| I




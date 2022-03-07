
# MIPSim
A MIPS assembly simulator written in C++

## Motivation
While I was suffering from lack of brilliant inspiration for new projects, I came up with this project since I had a class on MIPS assembly. 

## Features
- **Runs in Virtual Machine Code level**
Each instructions will be converted into machine codes that corresponds with MIPS assembly. `MIPSim` has built in `MachineCodeSimulator` and executes those operations.
- **OOP Style**
Each instructions are implemented as classes and its member functions. Thus modifying each instructions are easy.
## How to Use
There are two options of using this project in your own environment.
- Build this project using `cmake`

## Supported Instructions
Following instructions of MIPS assembly are currently supported with `MIPSim`. `MIPSim` is still in development phase, so there might be bugs and lack some important features.
|Instruction Name|OPCODE|FUNCT|Type|
|--|--|--|--|
|add|0x00|0x20| R  
|addi|0x08|NA| I 

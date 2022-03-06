# MIPSim
A MIPS assembly simulator written in Java

## Motivation
While I was suffering from lack of brilliant inspiration, I came up with this project since I had a class on MIPS assembly. 

## Features
- Instructions work in virtual machine code level.
Each instructions will be translate into MIPS assembly machine code and then will be executed using built in machine code engine.

## How to Use
There are two options of using this project in your own environment.
1. Download a compiled `.jar` file from release. 
2. `git clone` and `mvn install`.

## Supported Instructions
Following instructions of MIPS assembly are currently supported with `MIPSim`. `MIPSim` is still in development phase, so there might be bugs and lack some important features.
Instruction NameOPCODEFUNCT
------
add 0x00 0x20  
addi0x08NA
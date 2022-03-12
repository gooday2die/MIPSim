# Assembler
Assembler for `MIPSim` works like following flowchart

![enter image description here](https://raw.githubusercontent.com/gooday2die/MIPSim/cpp/github/pics/AssemblerFlowChart.png)

## Features
### As for now `MIPSim` assembler can...
- Translate register's mnemonics into register's indexes. (Ex `$zero` to `$0`)
- Detect if a Branch was duplicate
- Detect if a Branch's name is empty
- Detect if a Branch's name has whitespaces
- Detect if a Register was invalid. (Ex `$asdf` or `$35`)
- Check if arguments were correct (Ex `addiu` takes 2 register arguments and 1 immediate argument)
- Remove comments
- Skip empty lines
- Manage Branches
- Remove tabs and whitespaces before code (indentation)
- Replace two or more consecutive whitespaces into one whitespace
- Print out which line was incorrect with reason

### Is working on
- AST 
- Parsing
- Tokens
- Symbolic Table

## Special Features!
This feature is limited to Linux, however can print out in **colors**!
![enter image description here](https://raw.githubusercontent.com/gooday2die/MIPSim/cpp/github/pics/MIPSimColors.png)
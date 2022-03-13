# Tutorial
In this page, I am going to show you how `MIPSim` works with an example. 
### Universal
When you first run the program without arguments, it will show you an error that has no arguments.
```
$ ./MIPSim
Error: Empty arguments
Tip: Use --help to get information
```
### Arguments
- `--help` 

This option shows the help page for the program
- `-f` or `-file`

 This option assembles and simulates the code with the file provided. Example usage : 
 ```
$ ./MIPSim -f test.txt
 ```
- `--dev` 

This option shows developer's name with a smile
```
$ ./MIPSim --dev
By Gooday2die :b
https://github.com/gooday2die/MIPSim
```

### Errors
When `MIPSim` finds an error, it will display the error's reason and where the error is located at. For example, let's see an example code with three errors
```
# test.txt
sta rt:  # Error here
        aaandi $1, $1, 0 # Error Here
        andi $2, $2, 0 
        andi $5, $5, 0
        addi $52, $5, 4 # Error here
loop:
        addi $2, $2, 1 
        beq $2, $5, exit 
        j loop
exit:
        addi $10, $10, 100

```
When we execute the code with `MIPSim` the following output will be shown
```
$ ./MIPSim -f test.txt
===== MIPSim Assembler Version : 1.0.0 by Gooday2die =====
[ERROR] Branch name cannot contain whitespace @ln 0 -> sta rt:
[ERROR] Unknown Instruction mnemonic @ln 1 ->         aaandi $1, $1, 0 # a = 0;
[ERROR] Unknown register @ln 4 ->         addi $52, $5, 4 # c = c + 4;

Result :
Failed to assemble
Found 3 error(s)
```
*When `MIPSim` is built on Linux machine, the color is shown for easy representation. However when `MIPSim` is built on Windows machine, there are no colors with output.* 
#### Check **[here](https://github.com/gooday2die/MIPSim/tree/cpp/github/Assembler.md)** to see which error can be detected via `MIPSim` assembler.

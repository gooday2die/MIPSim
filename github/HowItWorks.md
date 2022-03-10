# How `MIPSim` works
This is a page that represents how `MIPSim` works with an example. Our example can be written in C code like it follows.
### C (or C++)
```
int main(void){
	uint32_t a = 0;
	uint32_t b = 0;
	uint32_t c = 0;
	
	c = c + 4;
	while(b != c) b = b + 1; // not b++ since b++ is not exactly the same
	a = 100;
}
```
### MIPS Assembly
An example of loop
```
start:
        andi $1, $1, 0 # a = 0;
        andi $2, $2, 0 # b = 0;
        andi $5, $5, 0 # c = 0;
        addi $5, $5, 4 # c = c + 4;
loop:
        addi $2, $2, 1 # b = b + 1;
        beq $2, $5, exit # break loop
        j loop 
exit:
        addi $10, $10, 100 # a = 100;
```

## Step 1. Preprocessing
This program does two steps in preprocessing
1. Removing all comments
2. Removing tabs before code

After preprocessing, our code will look like this:
```
start:
andi $1, $1, 0 
andi $2, $2, 0 
andi $5, $5, 0 
addi $5, $5, 4 
loop:
addi $2, $2, 1 
beq $2, $5, exit 
j loop 
exit:
addi $10, $10, 100 
```
## Step 2. Storing Expressions
This program will be storing each expressions inside `map` object. However it will **NOT** store branch in the `map`. Example is shown below. 
```
0:andi $1, $1, 0
1:andi $2, $2, 0
2:andi $5, $5, 0
3:addi $5, $5, 4
4:addi $2, $2, 1
5:beq $2, $5, exit
6:j loop
7:addi $10, $10, 100
```
## Step 3. Branches
When it is done storing expressions, now it is time for branches. Due to [limitations](https://github.com/gooday2die/MIPSim/blob/cpp/github/Limitations.md), **we will be treating branches as the index of each branch's first instruction's index**. There are 3 branches in this example code. 
```
start
loop
exit
```
Each will be represented as a `map` object in following formats.
```
exit:7
loop:4
start:0
```
Then the program will replace the all expression's branch strings into branch's value.
```
0:andi $1, $1, 0
1:andi $2, $2, 0
2:andi $5, $5, 0
3:addi $5, $5, 4
4:addi $2, $2, 1
5:beq $2, $5, 7
6:j 4
7:addi $10, $10, 100
```
## Step 4. Translating
When it is done branching, the program will now translate each expression into machine code instructions. Translated expressions as it follows.
```
Instruction# 0: 0x30210000
Instruction# 1: 0x30420000
Instruction# 2: 0x30a50000
Instruction# 3: 0x20a50004
Instruction# 4: 0x20420001
Instruction# 5: 0x10450006
Instruction# 6: 0x08000003
Instruction# 7: 0x214a0064
```
## Step 5. Simulating
When it successfully translated each expressions into machine codes, it will now simulate using class `Simulator`
```
Starting Job...
CURPC : 0x00000000 / MACHINECODE : 0x30210000
CURPC : 0x00000001 / MACHINECODE : 0x30420000
CURPC : 0x00000002 / MACHINECODE : 0x30a50000
CURPC : 0x00000003 / MACHINECODE : 0x20a50004
CURPC : 0x00000004 / MACHINECODE : 0x20420001
CURPC : 0x00000005 / MACHINECODE : 0x10450006
CURPC : 0x00000006 / MACHINECODE : 0x08000003
CURPC : 0x00000004 / MACHINECODE : 0x20420001
CURPC : 0x00000005 / MACHINECODE : 0x10450006
CURPC : 0x00000006 / MACHINECODE : 0x08000003
CURPC : 0x00000004 / MACHINECODE : 0x20420001
CURPC : 0x00000005 / MACHINECODE : 0x10450006
CURPC : 0x00000006 / MACHINECODE : 0x08000003
CURPC : 0x00000004 / MACHINECODE : 0x20420001
CURPC : 0x00000005 / MACHINECODE : 0x10450006
CURPC : 0x00000007 / MACHINECODE : 0x214a0064
Finished in 0.016000
```

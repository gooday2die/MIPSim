# Assembler V2
The old assembler was operating just by `string` operations. Assembler V2 is designed to work in the way how compilers and assembler works.
> My school never taught me compilers
> 
> Isu Kim

This code below is an expression MIPS assembly code. Now, I will be explaining each steps with this code and how this is converted.
```
start:
	li $v0, 100  # 0
	move $v0, $t0  # 1 
	ble $zero, $t0, a_b  # 2,3
	bge $t0, $zero, b_a  # 4,5
	j exit  # 6
a_b:
	li $t4, 150 # 7
	j exit  # 8
b_a:
	li $t4, 200 # 9
	j exit # 10
exit:
	li $t3 10000 # 11
```

## 0. Preprocessing
This step removes all unnecessary parts from the code that the programmer wrote by his/her editor. This process does the following things
- Removing indentations
- Removing comments
- Replacing tabs into whitespaces
- Replacing commas into whitespaces
- Replacing two or more consecutive whitespaces into one whitespace

### The result code till now
```
start:
li $v0 100 
move $v0 $t0 
ble $zero $t0 a_b 
bge $t0 $zero, b_a 
j exit 
a_b:
li $t4 150 
j exit 
b_a:
li $t4 200 
j exit 
exit:
li $t3 10000 
```


## 1. Lexical Analysis
This step is analyzing each **tokens**. The class that processes Lexical Analysis is `LexicalAnalyzer` defined in `LexicalAnalyzer.h`. This class can parse each expression's arguments and its type. Now our program looks at our original code in **tokens** like below.
```
0 : LABEL_TOKEN
1 : MNEMONIC_TOKEN REGISTER_TOKEN IMMEDIATE_TOKEN
2 : MNEMONIC_TOKEN REGISTER_TOKEN REGISTER_TOKEN
3 : MNEMONIC_TOKEN REGISTER_TOKEN REGISTER_TOKEN DEFINED_LABEL_TOKEN
4 : MNEMONIC_TOKEN REGISTER_TOKEN REGISTER_TOKEN DEFINED_LABEL_TOKEN
5 : MNEMONIC_TOKEN DEFINED_LABEL_TOKEN
6 : LABEL_TOKEN
7 : MNEMONIC_TOKEN REGISTER_TOKEN IMMEDIATE_TOKEN
8 : MNEMONIC_TOKEN DEFINED_LABEL_TOKEN
9 : LABEL_TOKEN
10 : MNEMONIC_TOKEN REGISTER_TOKEN IMMEDIATE_TOKEN
11 : MNEMONIC_TOKEN DEFINED_LABEL_TOKEN
12 : LABEL_TOKEN
13 : MNEMONIC_TOKEN REGISTER_TOKEN IMMEDIATE_TOKEN
```

Each tokens are represented as`enum Tokens` that was defined in `Token.h`. All those expressions and token strings will be turned into `std::pair<std::string, std::queue<Tokens>>` object. For example, the code `li $v0 100` will be saved in memory as following
```
<"li", queue[MNEMONIC_TOKEN, REGISTER_TOKEN, IMMEDIATE_TOKEN]>
```
## 2. Syntax Analysis
By the analyzed tokens and instruction mnemonics, now it is time for syntax analysis. Each mnemonic instructions have a specific argument order that is stored in a queue. For example, instruction `li` is defined as following.
```
"li" : MNEMONIC_TOKEN REGISTER_TOKEN IMMEDIATE_TOKEN
```
If our expression that was analyzed by Lexical Analysis matches the same format as its original format, it means that the syntax was correct. For example it works in the way below.
```
li $v0 100 
```
Will be translated into tokens by Lexical Analysis in the following order:
```
MNEMONIC_TOKEN REGISTER_TOKEN IMMEDIATE_TOKEN
```
Since our original instruction token order matches with the expression `li $v0 100`, this is considered a correct syntax. Next, I will be showing you a wrong expression. Consider, following expression which is wrong by syntax.
```
li $v0 $v0 100 
```
This will be translated into tokens by Lexical Analysis in the following order:
```
MNEMONIC_TOKEN REGISTER_TOKEN REGISTER_TOKEN IMMEDIATE_TOKEN
```
This order does **not** match the original `li`'s argument orders and types. Thus will be resulting `ExpressionExceptions::invalidArgumentException` defined in `Errors.h`. All exceptions and errors related to grammars are defined as `class` in file `Errors.h`.
### Till this step, the assembler did NOT generate any machine codes at all.

## 3. Semantic Analysis
Yes, assembler does not need semantic analysis. Also in `MIPSim` it does not use ASTs for semantic analysis. The main difference between *Syntax Analysis* is that *Syntax Analysis* just checks syntax by with tokens. This will only check if the token order and count was correct. However with this method, *Syntax Analysis* cannot find semantic errors at all. Look at an example below.

```
$tart:
```
This will be translated into `LabelDefinitionToken`. This means that with *Syntax Analysis*, this expression will be considered correct. However this is not correct with `MIPSim` grammar. Since it includes special character (`$`) in the branch's name. *Semantic Analysis* provides extra layer of detecting flaws in grammars or any flaws that might potentially cause errors during simulation runtime. 
### Till this step, the assembler did NOT generate any machine codes at all.

## 4. Translating
After all expressions have passed grammar, it is now time for translating. In this step, the expression that was written in expressions as human-friendly (*MIPS is not that human-friendly, however at least it is human-friendly compared to 32bit hex codes*) to machine code instructions. In this step, **translator assumes all expressions are correct and has no grammatical errors**. This means that if there were any errors that were not detected during grammar checking phase from **Step 1 ~ 3**, this might cause translator to fail translating. When there was a error or exception with translator, this will output text in following format
```
[TRANSLATOR ERROR] error reasons.
```
Since `MIPSim` is still in development phase, as well as I have never had a compiler class before, there might be some unexpected translator errors or bugs. So, if you happen to find any bugs or errors while running this in your environment, please open an issue with the code snippet in this GitHub repository so that I can look into those bugs. 

### Example with example
```
start:  
   li $v0, 100  # 0  
   move $v0, $t0  # 1   
   ble $zero, $t0, a_b  # 2,3  
   bge $t0, $zero, b_a  # 4,5  
   j exit  # 6  
a_b:  
   li $t4, 150 # 7  
   j exit  # 8  
b_a:  
   li $t4, 200 # 9  
   j exit # 10  
exit:  
   li $t3 10000 # 11
```
Let's assume that we have an code snippet above. When `MIPSim` translates it to machine language, the following steps will be executed in order.

#### Step1. Scanning and storing all labels
All labels regardless of its section type, `MIPSim` loads all labels and stores their address. 
```
Label Name : a_b @ 7
Label Name : b_a @ 9
Label Name : exit @ 11
Label Name : start @ 0
```
#### Step2. Translating pseudo instructions into normal instructions
This step translates pseudo instructions into normal instructions. Pseudo instructions are **not** a real instruction. Thus it should be translated into normal instructions.
```
li $v0, 100  # li is a pseudo instruction. 
```
This pseudo instruction will be translated into following expression
```
ori $0 $v0 100
```
These expressions will be stored in a vector of string that represents all expressions. 
 #### Step3. Translating normal instructions
Each arguments are going to be parsed in the type that was provided by *Lexical Analysis* and are translated into machine codes. The code snippet will be translated by tokens in following forms.
```
ori $0 $v0 100  -> Register $0 Register $2 Immediate Value 100
addu $v0 $0 $t0  -> Register $2 Register $0 Register $8
slt $t0 $zero $at  -> Register $8 Register $0 Register $1
beq $at $zero a_b  -> Register $1 Register $0 Address Value 7
slt $t0 $zero $at  -> Register $8 Register $0 Register $1
beq $at $zero b_a  -> Register $1 Register $0 Address Value 9
j exit  -> Address Value 11
ori $0 $t4 150  -> Register $0 Register $12 Immediate Value 150
j exit  -> Address Value 11
ori $0 $t4 200  -> Register $0 Register $12 Immediate Value 200
j exit  -> Address Value 11
ori $0 $t3 10000  -> Register $0 Register $11 Immediate Value 10000
```
When it is done translating all arguments by its token types, `MIPSim` now will translate them into real machine codes.
```
Expression 0: 0x34020064
Expression 1: 0x00404021
Expression 2: 0x0100082a
Expression 3: 0x10200007
Expression 4: 0x0100082a
Expression 5: 0x10200009
Expression 6: 0x0800000b
Expression 7: 0x340c0096
Expression 8: 0x0800000b
Expression 9: 0x340c00c8
Expression 10: 0x0800000b
Expression 11: 0x340b2710
```
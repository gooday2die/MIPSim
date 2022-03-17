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

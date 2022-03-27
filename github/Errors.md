# Errors
This page is for explaining each errors and how they are detected with error examples. Our assembler **does not** allow any errors to be compiled. When a single error was found in the code that was being assembled, it **gives up** assembling the expressions into machine code. 
### How `MIPSim` checks grammar
`MIPSim` checks grammar in three different stages in order.
1. Lexical Analysis
2. Syntax Analysis
3. Semantic Analysis

This means that if an expression had multiple grammatical errors, the latter analysis cannot catch extra errors since the earlier analysis caught the expression as error already. For example, if an expression had syntax error and semantic error, assembler will catch only syntax errors and will disregard semantic errors since there already was an error in the expression.
## Invalid argument found
**Detection Phase** : Syntax Analysis
**Detection Conditions** : When the expression did not match the type of arguments and orders of the instruction syntax.
**Error Example**:
```
li $v0 100 $10 # li takes MNEMONIC_TOKEN REGISTER_TOKEN IMMEDIATE_TOKEN
```
**Assembler Output**:
```
[ERROR] Invalid argument found  @ln 1 -> li $v0 100 $10
```

## Unknown token was found
**Detection Phase** : Lexical Analysis
**Detection Conditions** : When expression contained a token that was unknown.
**Error Example**:
```
asdf # asdf is not defined as a MIPS instruction
```
**Assembler Output**:
```
[ERROR] Unknown token was found  @ln 1 -> asdf
```

## Immediate value without expression was found
**Detection Phase** : Syntax Analysis
**Detection Conditions** : When a bare immediate token was found without any expression
**Error Example**:
```
100 # immediate value 100 was used without any context
```
**Assembler Output**:
```
[ERROR] Immediate value without expression was found  @ln 1 -> 100 
```

## Register without expression was found
**Detection Phase** : Syntax Analysis
**Detection Conditions** : When a bare register token was found without any expression
**Error Example**:
```
$t3 # register $t3 was used without any context
```
**Assembler Output**:
```
[ERROR] Register without expression was found  @ln 1 -> $t3 
```

## Label value without expression was found
**Detection Phase** : Syntax Analysis
**Detection Conditions** : When a bare label token was found without any expression
**Error Example**:
```
start # label start was used without any context
```
**Assembler Output**:
```
[ERROR] Label value without expression was found  @ln 1 -> start
```

## String without expression was found
**Detection Phase** : Semantic Analysis
**Detection Conditions** : When a bare string token was found without any expression
**Error Example**:
```
"hello!"
```
**Assembler Output**:
```
[ERROR] String without expression was found  @ln 1 -> "hello!"
```

## Duplicate label declaration was found
**Detection Phase** : Semantic Analysis
**Detection Conditions** : When there was a label with same name was declared before
**Error Example**:
```
:start # first declaration
:start # second declaration
```
**Assembler Output**:
```
[ERROR] Duplicate label declaration was found  @ln 1 -> start:
```

## Token was found in wrong code section
**Detection Phase** : Semantic Analysis
**Detection Conditions** : When a token was used in a wrong section. For example if a `text` section had `Data Definition` or a `data` section had other tokens than `Data Definition`.
**Error Example**:
```
.text # text section was declared
.asciiz hi "hello world!" # .asciiz has to be declared inside a .data section
```
**Assembler Output**:
```
[ERROR] Token was found in wrong code section  @ln 2 -> .asciiz hi "hello world!"
```
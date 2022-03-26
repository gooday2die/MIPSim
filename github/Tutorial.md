# Tutorial
This page contains tutorials of `MIPSim` and examples of running the program. We will be using a test file `./demo/loop_test.txt` that contains following instructions.

```
start:
        andi $1, $1, 0 # a = 0;
        andi $2, $2, 0 # b = 0;
        andi $5, $5, 0 # c = 0;
        addi $5, $5, 4 # c = c + 4;
loop:
        addi $2, $2, 1 # b = b + 1;
        beq $2, $5, exit # break loop
        j loop ## BUG FOUND
exit:
        addi $10, $10, 100 # a = 100;
```

## Without Args
```
$ ./MIPSim
Error: Empty arguments
Tip: Use --help to get information
```

## Help 
```
$ ./MIPSim --help
===== MIPSim Assembler Version : 1.0.0 by Gooday2die =====
 --help : prints out this page
 --dev : show developer credit
 -rf, -runfile fileName : assemble and simulate specified file
 -a, -assemble fileName : assemble and print out the translated expressions of specified file
``` 
Argument `--help` prints out help messages
## Dev
```
$ ./MIPSim --dev
 _____ ______   ___  ________  ________  ___  _____ ______
|\   _ \  _   \|\  \|\   __  \|\   ____\|\  \|\   _ \  _   \
\ \  \\\__\ \  \ \  \ \  \|\  \ \  \___|\ \  \ \  \\\__\ \  \
 \ \  \\|__| \  \ \  \ \   ____\ \_____  \ \  \ \  \\|__| \  \
  \ \  \    \ \  \ \  \ \  \___|\|____|\  \ \  \ \  \    \ \  \
   \ \__\    \ \__\ \__\ \__\     ____\_\  \ \__\ \__\    \ \__\
    \|__|     \|__|\|__|\|__|    |\_________\|__|\|__|     \|__|
                                 \|_________|
                                                    Version : 1.0.0
                                                   By Gooday2die :b
                               https://github.com/gooday2die/MIPSim

```
Argument `--dev` prints out version information.

## Assemble
```
$ ./MIPSim -assemble ./loop_test.txt
===== MIPSim Assembler Version : 1.0.0 by Gooday2die =====
Assembling...
Successfully assembled
Branch Name : exit @ 0x0040001c
Branch Name : loop @ 0x00400010
Branch Name : start @ 0x00400000
Expression 0x00400000 : 0x30210000
Expression 0x00400004 : 0x30420000
Expression 0x00400008 : 0x30a50000
Expression 0x0040000c : 0x20a50004
Expression 0x00400010 : 0x20420001
Expression 0x00400014 : 0x10450002
Expression 0x00400018 : 0x08100004
Expression 0x0040001c : 0x214a0064
Assembled 8 expression(s)
Generated 3 label(s)

```
Argument `-a` or `-assemble` prints out all translated machine codes from the file that was given as an input. This just **assembles** the file however does **NOT** execute file.
### Errors - Without file name
```
$ ./MIPSim -assemble
Error: Missing filename
```
### Errors - Cannot find file
```
$ ./MIPSim -assemble unknown.txt
[Error] Cannot locate file: unknown.txt
```
Depending on the OS, there might be `Segmentation fault (core dumped)` instead of nice message

### Errors - Grammatical Error
#### File with errors : `./demo/error_test.txt`
```
.text
start:
	li $v0, 100  # 0
	li $v0, 100, $10  # 0
	move $v0, $t0  # 1
	ble $zero, $t0, a_b  # 2,3
	.asciiz
	exit
	$t0
	100
asdf
.data
.text
start:
	bge $t0, $zero, b_a  # 4,5
	j exit  # 6
	start
a_b:
	li $t4, 150 # 7
	j exit  # 8
b_a:
	li $t4, 200 # 9
	j exit # 10
exit:
	li $t3 10000 # 11
.asciiz
```
With the code above, following results are given out.
```
$ ./MIPSim -assemble error_test.txt
[ERROR] Invalid argument found  @ln 3 -> li $v0 100 $10
[ERROR] Token was found in wrong code section  @ln 6 -> .asciiz
[ERROR] Label value without expression was found  @ln 7 -> exit
[ERROR] Register without expression was found  @ln 8 -> $t0
[ERROR] Immediate value without expression was found  @ln 9 -> 100
[ERROR] Unknown token was found  @ln 10 -> asdf
[ERROR] Duplicate label declaration was found  @ln 13 -> start:
[ERROR] Label value without expression was found  @ln 16 -> start
[ERROR] Token was found in wrong code section  @ln 25 -> .asciiz
Failed to assemble
Found 9 error(s)
```

## Run File
```
gooday2die@flagship:~/projects/MIPSim/bd$ ./MIPSim -rf loop_test.txt
===== MIPSim Assembler Version : 1.0.0 by Gooday2die =====
Assembling...
Successfully assembled
Branch Name : exit @ 0x0040001c
Branch Name : loop @ 0x00400010
Branch Name : start @ 0x00400000
Expression 0x00400000 : 0x30210000
Expression 0x00400004 : 0x30420000
Expression 0x00400008 : 0x30a50000
Expression 0x0040000c : 0x20a50004
Expression 0x00400010 : 0x20420001
Expression 0x00400014 : 0x10450002
Expression 0x00400018 : 0x08100004
Expression 0x0040001c : 0x214a0064
Assembled 8 expression(s)
Generated 3 label(s)

===== MIPSim Version : 1.0.0 by Gooday2die =====
Starting Job...
Current Address : 0x00400000 / MACHINECODE : 0x30210000
Current Address : 0x00400004 / MACHINECODE : 0x30420000
Current Address : 0x00400008 / MACHINECODE : 0x30a50000
Current Address : 0x0040000c / MACHINECODE : 0x20a50004
Current Address : 0x00400010 / MACHINECODE : 0x20420001
Current Address : 0x00400014 / MACHINECODE : 0x10450002
Current Address : 0x00400018 / MACHINECODE : 0x08100004
Current Address : 0x00400010 / MACHINECODE : 0x20420001
Current Address : 0x00400014 / MACHINECODE : 0x10450002
Current Address : 0x00400018 / MACHINECODE : 0x08100004
Current Address : 0x00400010 / MACHINECODE : 0x20420001
Current Address : 0x00400014 / MACHINECODE : 0x10450002
Current Address : 0x00400018 / MACHINECODE : 0x08100004
Current Address : 0x00400010 / MACHINECODE : 0x20420001
Current Address : 0x00400014 / MACHINECODE : 0x10450002
Current Address : 0x0040001c / MACHINECODE : 0x214a0064
Finished in 0.000100
Registers:
$ 0 : hex : 0x00000000 / signed int : 0
$ 1 : hex : 0x00000000 / signed int : 0
$ 2 : hex : 0x00000004 / signed int : 4
$ 3 : hex : 0x00000000 / signed int : 0
$ 4 : hex : 0x00000000 / signed int : 0
$ 5 : hex : 0x00000004 / signed int : 4
$ 6 : hex : 0x00000000 / signed int : 0
$ 7 : hex : 0x00000000 / signed int : 0
$ 8 : hex : 0x00000000 / signed int : 0
$ 9 : hex : 0x00000000 / signed int : 0
$10 : hex : 0x00000064 / signed int : 100
$11 : hex : 0x00000000 / signed int : 0
$12 : hex : 0x00000000 / signed int : 0
$13 : hex : 0x00000000 / signed int : 0
$14 : hex : 0x00000000 / signed int : 0
$15 : hex : 0x00000000 / signed int : 0
$16 : hex : 0x00000000 / signed int : 0
$17 : hex : 0x00000000 / signed int : 0
$18 : hex : 0x00000000 / signed int : 0
$19 : hex : 0x00000000 / signed int : 0
$20 : hex : 0x00000000 / signed int : 0
$21 : hex : 0x00000000 / signed int : 0
$22 : hex : 0x00000000 / signed int : 0
$23 : hex : 0x00000000 / signed int : 0
$24 : hex : 0x00000000 / signed int : 0
$25 : hex : 0x00000000 / signed int : 0
$26 : hex : 0x00000000 / signed int : 0
$27 : hex : 0x00000000 / signed int : 0
$28 : hex : 0x00000000 / signed int : 0
$29 : hex : 0x00000000 / signed int : 0
$30 : hex : 0x00000000 / signed int : 0
$31 : hex : 0x00000000 / signed int : 0
```
### Errors - Without file name
Same as `Assemble` argument
### Errors - Cannot find file
Same as `Assemble` argument
### Errors - Grammatical Error
Same as `Assemble` argument

#### Check **[here](https://github.com/gooday2die/MIPSim/tree/cpp/github/AssemblerV2.md)** to see which error can be detected via `MIPSim` assembler.
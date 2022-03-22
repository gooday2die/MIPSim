## Limitations to Implementations
I am just a sophomore CS student and I do not have that much knowledge about MIPS or computer architecture. Thus there are some limitations to this program and this might **NOT** work as how computers operate. Those following list is that is **NOT** implemented in this program.

## Machine Codes
In this program, the machine codes are just stored as a `uint32_t`. Since MIPS32 architecture just needs 32 bits for its instructions, thus a `uint32_t` will be enough to store each machine codes. Those machine codes are stored in a `uint32_t` array that is inside class `Simulator`. Instead of them having real `address`, they have `index` since they are inside an array.

## PC
`PC` is the most important feature with MIPS assembly. However in this program `PC` is implemented as a `uint32_t` variable that stores the next `index` of the machine code stored in class `Simulator` instead of `address` of next instruction.

## Labels
The most limitations located with labels. There are two types of labels supported by `MIPSim`. 
1. **Text Section**

There are two types of labels that can be used in assembly code. 
### **Using labels as immediate (Relative addresses)**

Some expressions use immediate values in order to represent label addresses. Those immediate values represent the distance between the branch instruction's address and current expression's address. For example, let's see an example below.
```
near_instruction_1:
	li $t2 20                          # instruction stored in 0x00400000
start: 
	beq $zero, $t0, near_instruction_2 # instruction stored in 0x00400004
	beq $t1, $t0, near_instruction_1   # instruction stored in 0x00400008
near_instruction_2 :
	li $t2 10                          # instruction stored in 0x0040000C
```
With the example above, the branch labels for following expressions would be following values.

- `beq $zero, $t0, near_instruction_2` : the `near_instruction_2` will be represented `+1 ` since the branch `near_instruction_2` has `+1` distance from the original. Will be represented as `0x0001`
- `beq $t1, $t0, near_instruction_1` : the `near_instruction_1` will be represented `-2` since the branch `near_instruction_1` has `-2` distance from the original. Will be represented as `0xFFFD`
#### Note that the PC adds +1 to the relative address. Thus the calculation between the expressions would be: `destination address - current address - 1`

However, using labels as immediate value is **NOT** enough to cover all addresses. For example, `bne` and `beq` instructions use labels for branch controls. However both instructions are `I type`, which uses LSB **16 bits** as its immediate value. However, since `MIPS` uses **32 bit** address system for its text section from `0x00400000` to `0x10000000`, it is **NOT** possible to cover full **32 bits** using only one single `bne` and `beq` expressions since their limitations for branching and jumping over PC is limited to maximum `0x0FFF`. For example, let's see an example below. 
```
start: 
	beq $zero, $t0, far_away # instruction stored at 0x00400000
	... 
far_away :
	li $t2 10                # instruction stored at 0x00500000
```
By the example above, it shows the label `far_away` cannot be reached using single `beq` instruction since `beq`'s immediate value can maximum cover from `0x0040000` to `0x00403FFC`. Thus this means that the maximum range that a single branch control can cover is maximum `4095` expression. If you would like to make more than `4095` expressions, you **MUST** connect branch controls like example below.
```
start: 
	beq $zero, $t0, con_1      # instruction stored at 0x00400000
	... 
con_1:
	beq $zero, $zero, con_2    # instruction stored at 0x00402FFC
con_2:
	beq $zero, $zero, con_3    # instruction stored at 0x00404FFC
...
far_away :
	li $t2 10                  # instruction stored at 0x00500000
```

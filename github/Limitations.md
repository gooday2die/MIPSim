## Limitations to Implementations
I am just a sophomore CS student and I do not have that much knowledge about MIPS or computer architecture. Thus there are some limitations to this program and this might **NOT** work as how computers operate. Those following list is that is **NOT** implemented in this program.

### Machine Codes
In this program, the machine codes are just stored as a `uint32_t`. Since MIPS32 architecture just needs 32 bits for its instructions, thus a `uint32_t` will be enough to store each machine codes. Those machine codes are stored in a `uint32_t` array that is inside class `Simulator`. Instead of them having real `address`, they have `index` since they are inside an array.

### PC
`PC` is the most important feature with MIPS assembly. However in this program `PC` is implemented as a `uint32_t` variable that stores the next `index` of the machine code stored in class `Simulator` instead of `address` of next instruction.

### Branch
Branch feature of MIPS architecture is **NOT** implemented as how it is designed in real MIPS. In this program, the branches are stored as an array of `uint32_t` inside class `Simulator`. Each `branch` variables store the `index` that contains the `branch`'s starting machine code. That being said, following instructions are **NOT** implemented as how it works originally with MIPS architecture
- `beq` : This instruction was supposed to have `PC=PC+4+BranchAddr` as its operation. However this is not implemented this way. By `beq` operation, this will just set the `PC`'s value into the `index` of the branch's first machine code.
- `bne` : This instruction was supposed to have `PC=PC+4+BranchAddr` as its operation. However this is not implemented this way. By `beq` operation, this will just set the `PC`'s value into the `index` of the branch's first machine code.

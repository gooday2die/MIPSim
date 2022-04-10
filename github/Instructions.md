## Supported Instructions
Following instructions of MIPS assembly are currently supported with `MIPSim`. `MIPSim` is still in development phase, so there might be bugs or lack some important features.
### Normal Instructions
|Instruction Name|OPCODE|FUNCT|Type|ETC|
|--|--|--|--|--|
|add|0x00|0x20| R | Overflow Detection
|addi|0x08|NA| I 
|addiu|0x09|NA| I 
|addu|0x00|0x21| R | Overflow Detection
|and|0x00|0x24| R 
|andi|0x0C|NA| I
|beq|0x04|NA| I | Limitations ([here](https://github.com/gooday2die/MIPSim/blob/cpp/github/Limitations.md))
|bne|0x05|NA| I | Limitations ([here](https://github.com/gooday2die/MIPSim/blob/cpp/github/Limitations.md))
|j|0x02|NA| J
|jal|0x03|NA| J
|jr|0x00|0x08| R
|nor|0x00|0x27| R
|or|0x00|0x25| R
|ori|0x0D|NA| I
|slt|0x00|0x2A| I
|slti|0x0A|NA| I
|sltiu|0x0B|NA| I
|sltu|0x00|0x2B| I
|sll|0x00|0x00| I
|srl|0x00|0x02| I
|sub|0x00|0x22| I | Overflow Detection
|subu|0x00|0x23| I

### Pseudo-Instructions
|Instruction Name|Translated Instructions|ETC|
|--|--|--|
|li|`ori`|NA|
|move|`addu`|NA|
|bgt|`slt`, `bne`|NA|
|bge|`slt`, `beq`|NA|
|blt|`slt`, `bne`|NA|
|ble|`slt`, `beq`|NA|

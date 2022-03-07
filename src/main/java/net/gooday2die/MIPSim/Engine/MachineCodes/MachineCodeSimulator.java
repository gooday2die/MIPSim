package net.gooday2die.MIPSim.Engine.MachineCodes;


import net.gooday2die.MIPSim.Engine.Instructions.InstructionActor;
import net.gooday2die.MIPSim.Engine.MIPSim;
import net.gooday2die.MIPSim.Engine.Register;
import net.gooday2die.MIPSim.Engine.RegisterHandler;

/**
 * A class for simulating machine codes
 * @author Gooday2die (Isu Kim)
 */
public class MachineCodeSimulator {
    private RegisterHandler rh;

    /**
     * An exception class for invalid instructions.
     * This will be thrown when the opcode and Funct (if exits) is wrong.
     */
    public static class InvalidInstruction extends Exception{
        public InvalidInstruction(String errorMessage){
            super(errorMessage);
        }
    }

    /**
     * A constructor method for class MachineCodeSimulator
     * @param registerHandler the RegisterHandler object for all registers
     */
    public MachineCodeSimulator(RegisterHandler registerHandler){
        rh = registerHandler;
    }
    /**
     * A method for executing a machine code
     * @param code the MachineCode object of code to simulate and execute
     * @return returns true if successful, false if not
     * @throws RegisterHandler.InvalidRegisterIndex is thrown when the register index was invalid (would not happen)
     */
    public boolean executeCode(MachineCode code) throws RegisterHandler.InvalidRegisterIndex, InvalidInstruction {
        int curCode = code.getCode();
        int codeType = code.getCodeType();

        switch(codeType){
            case 1 -> { // for R types
                int opcode = curCode >> 26; // shifting 26 times will get opcode
                int rs = (curCode >> 21) & 0x1F; // shifting 21 times and doing & with 0x1F will get rs value
                int rt = (curCode >> 16) & 0x1F; // shifting 16 times and doing & with 0x1F will get rt value
                int rd = (curCode >> 11) & 0x1F; // shifting 11 times and doing & with 0x1F will get rd value
                int shamt = (curCode >> 6) & 0x1F; // shifting 6 times and doing & with 0x1F will get shamt value
                int funct = curCode & 0x3F; // doing & with 0x3F will get funct value
                //System.out.println("OPCODE : " + opcode + " rs : " + rs + " rt : " + rt + " rd : " + rd +
                //        " shamt : " + shamt + " funct : " + funct);

                switch(opcode & 0x3F){
                    case 0x00 -> {
                        switch (funct & 0x3F) {
                            case 0x20 -> { // opcode 0x00 and funct 0x20 = add instruction
                                InstructionActor.add.execute(rh.getRegister(rs), rh.getRegister(rt), rh.getRegister(rd));
                            }
                            default -> throw new InvalidInstruction("Invalid OPCODE : " + opcode + " and FUNCT : " + funct);
                        }
                    }
                    default -> throw new InvalidInstruction("Invalid OPCODE : " + opcode + " and FUNCT : " + funct);
                }
            }
            case 2 -> { // for I types
                int opcode = curCode >> 26; // shifting 26 times will get opcode
                int rs = (curCode >> 21) & 0x1F; // shifting 21 times and doing & with 0x1F will get rs value
                int rt = (curCode >> 16) & 0x1F; // shifting 16 times and doing & with 0x1F will get rt value
                int imm = curCode & 0xFFFF; // doing & with 0xFFFF will get imm value
                //System.out.println("OPCODE : " + opcode + " rs : " + rs + " rt : " + rt + " imm : " + imm);
                switch (opcode & 0x3F) {
                    case 0x08 -> InstructionActor.addi.execute(rh.getRegister(rs), rh.getRegister(rt), imm);
                    case 0x09 -> InstructionActor.addiu.execute(rh.getRegister(rs), rh.getRegister(rt), imm);
                    default -> throw new InvalidInstruction("Invalid OPCODE : " + opcode);

                }
            }
            case 3 -> { // for J types
                int opcode = curCode >> 26; // shifting 26 times will get opcode
                int address = curCode & 0x3FFFFFF; // doing & with 0x3FFFFFF will get address value
                // System.out.println("OPCODE : " + opcode + " address : " + address);
            }
        }
        return true;
    }
}

package net.gooday2die.MIPSim.Engine.MachineCodes;


/**
 * A class for simulating machine codes
 * @author Gooday2die (Isu Kim)
 */
public class MachineCodeSimulator {
    /**
     * A method for executing a machine code
     * @param code the MachineCode object of code to simulate and execute
     * @return returns true if successful, false if not
     */
    public static boolean executeCode(MachineCode code){
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
                System.out.println("OPCODE : " + opcode + " rs : " + rs + " rt : " + rt + " rd : " + rd +
                        " shamt : " + shamt + " funct : " + funct);
            }
            case 2 -> { // for I types
                int opcode = curCode >> 26; // shifting 26 times will get opcode
                int rs = (curCode >> 21) & 0x1F; // shifting 21 times and doing & with 0x1F will get rs value
                int rt = (curCode >> 16) & 0x1F; // shifting 16 times and doing & with 0x1F will get rt value
                int imm = curCode & 0xFFFF; // doing & with 0xFFFF will get imm value
                System.out.println("OPCODE : " + opcode + " rs : " + rs + " rt : " + rt + " imm : " + imm);
            }
            case 3 -> { // for J types
                int opcode = curCode >> 26; // shifting 26 times will get opcode
                int address = curCode & 0x3FFFFFF; // doing & with 0x3FFFFFF will get address value
                System.out.println("OPCODE : " + opcode + " address : " + address);
            }
        }
        return true;
    }
}

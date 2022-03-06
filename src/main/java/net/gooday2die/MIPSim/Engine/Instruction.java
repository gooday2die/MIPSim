package net.gooday2die.MIPSim.Engine;

/**
 * A class for all instructions
 * @author Gooday2die (Isu Kim)
 */
public class Instruction{
    /**
     * A class for add instruction
     */
    public static class add extends abstractInstruction.RType{
        static void execute(Register rs, Register rt, Register rd) {
            int rsValue = rs.getValue();
            int rtValue = rt.getValue();
            int rdValue = rsValue + rtValue;
            rd.setValue(rdValue);
        }
    }

    /**
     * A class for addi instruction
     */
    public static class addi extends abstractInstruction.IType{
        static void execute(Register rs, Register rt, int immediate) {
            int rsValue = rs.getValue();
            int rtValue = rsValue + immediate;
            rt.setValue(rtValue);
        }
    }
}
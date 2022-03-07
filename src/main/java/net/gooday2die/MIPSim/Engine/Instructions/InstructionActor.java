package net.gooday2die.MIPSim.Engine.Instructions;

import net.gooday2die.MIPSim.Engine.Register;

/**
 * A class for all instructions
 * @author Gooday2die (Isu Kim)
 */
public class InstructionActor {
    /**
     * A class for add instruction
     */
    public static class add extends AbstractInstruction.RType{
        public static void execute(Register rs, Register rt, Register rd) {
            int rsValue = rs.getValue();
            int rtValue = rt.getValue();
            int rdValue = rsValue + rtValue;
            rd.setValue(rdValue);
        }
    }

    /**
     * A class for addi instruction
     */
    public static class addi extends AbstractInstruction.IType{
        public static void execute(Register rs, Register rt, int immediate) {
            int rsValue = rs.getValue();
            int rtValue = rsValue + (short) immediate; // need type casting since it is signed short (16bits)
            rt.setValue(rtValue);
        }
    }

    /**
     * A class for addiu instruction
     */
    public static class addiu extends AbstractInstruction.IType{
        public static void execute(Register rs, Register rt, int immediate) {
            int rsValue = rs.getValue();
            int rtValue = rsValue + Short.toUnsignedInt((short) immediate); // since immediate is unsigned
            rt.setValue(rtValue);
        }
    }
}
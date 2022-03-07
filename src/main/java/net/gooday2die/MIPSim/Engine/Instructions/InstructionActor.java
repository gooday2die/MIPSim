package net.gooday2die.MIPSim.Engine.Instructions;

import net.gooday2die.MIPSim.Engine.Register;

/**
 * A class for all instructions
 * @author Gooday2die (Isu Kim)
 */
public class InstructionActor {
    /**
     * A class for add instruction
     * MIPS add instruction raises exception when the instruction had overflow in the result.
     * This exception is implemented as OverflowException
     */
    public static class add extends AbstractInstruction.RType{
        public static void execute(Register rs, Register rt, Register rd) throws OverflowException {
            long rsValue = rs.getValue();
            long rtValue = rt.getValue();
            long rdValue = rsValue + rtValue;

            if (rdValue > Long.parseLong("ffffffff", 16))
                // Java works super dumb. It does not recognize 0xFFFFFFFF as unsigned value at all.
                // This recognize as -1 which is signed integer by default.
                // The way of going around this would be parsing ffffffff
                throw new OverflowException("result overflowed");
            else { // if it was normal case
                rd.setValue((int)rdValue);
            }
        }

        /**
         * A class for overflow exception when add operation had an overflow.
         */
        public static class OverflowException extends Exception{
            public OverflowException(String errorMessage){
                super(errorMessage);
            }
        }
    }

    /**
     * A class for add instruction
     * unlike add instruction, addu does not take care of the overflow
     */
    public static class addu extends AbstractInstruction.RType{
        public static void execute(Register rs, Register rt, Register rd) {
            long rsValue = rs.getValue();
            long rtValue = rt.getValue();
            long rdValue = rsValue + rtValue;
            rd.setValue((int)rdValue);
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
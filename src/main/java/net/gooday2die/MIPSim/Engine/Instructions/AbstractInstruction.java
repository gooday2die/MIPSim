package net.gooday2die.MIPSim.Engine.Instructions;


import net.gooday2die.MIPSim.Engine.Register;

/**
 * A class for abstract instructions
 * @author Gooday2die (Isu Kim)
 */
public class AbstractInstruction {
    /**
     * An abstract class for R Type instructions.
     * This should be extended by real Instructions.
     */
    public abstract static class RType{
        /**
         * An abstract method for executing the R Type instruction
         * @param rs int object that represents index of rs register
         * @param rt int object that represents index of rt register
         * @param rd int object that represents index of rd register
         */
        static void execute(Register rs, Register rt, Register rd) throws InstructionActor.OverflowException, InstructionActor.OverflowException {}
    }

    /**
     * An abstract class for I Type instructions.
     * This should be extended by real Instructions.
     */
    public abstract static class IType{
        /**
         * An abstract method for executing the I Type instruction
         * @param rs int object that represents index of rs register
         * @param rt int object that represents index of rt register
         * @param immediate int object that represents value of immediate
         */
        static void execute(Register rs, Register rt, int immediate) throws InstructionActor.OverflowException {}
    }

    /**
     * An abstract class for J Type instructions.
     * This should be extended by real Instructions.
     */
    public abstract static class JType{
        /**
         * An abstract method for executing J Type instruction
         * @param address int object that represents address of the instruction
         */
        abstract void execute(int address);
    }
}
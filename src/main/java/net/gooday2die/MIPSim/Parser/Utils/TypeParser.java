package net.gooday2die.MIPSim.Parser.Utils;


/**
 * A class that parses type regarding on each instruction's types
 * @author Gooday2die (Isu Kim)
 */
public class TypeParser {
    /**
     * A exception class when the instruction was invalid.
     */
    public static class InvalidInstruction extends Exception{
        public InvalidInstruction(String errorMessage){
            super(errorMessage);
        }
    }

    /**
     * A method for finding which instruction type this instruction matches
     * R Type instructions will be returned as 1
     * I Type instructions will be returned as 2
     * J Type instructions will be returned as 3
     * @param instructionString the string that represents current instruction
     * @return returns integer type object that matches its type
     */
    public static int parse(String instructionString) throws InvalidInstruction{
        return switch (instructionString) {
            case "add" -> 1;
            case "addi" -> 2;
            default -> throw new InvalidInstruction("Invalid instruction type : " + instructionString);
        };
    }
}

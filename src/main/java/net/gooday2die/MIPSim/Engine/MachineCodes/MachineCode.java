package net.gooday2die.MIPSim.Engine.MachineCodes;

/**
 * A class that represents a single machine code
 * R Type instructions will be returned as 1
 * I Type instructions will be returned as 2
 * J Type instructions will be returned as 3
 * @author Gooday2die (Isu Kim)
 */
public class MachineCode {
    private final int code; // the machine code to set
    private final int codeType;
    /**
     * A constructor method for class MachineCode
     * @param machineCode the machine code integer to set
     * @param argCodeType the type to set
     */
    public MachineCode(int machineCode, int argCodeType){
        code = machineCode;
        codeType = argCodeType;
    }

    /**
     * A getter method for attribute code
     * @return returns integer value of code
     */
    public int getCode() {
        return code;
    }

    /**
     * A getter method for attribute code Type
     * @return returns type object of this current machine code
     */
    public int getCodeType(){
        return codeType;
    }
}

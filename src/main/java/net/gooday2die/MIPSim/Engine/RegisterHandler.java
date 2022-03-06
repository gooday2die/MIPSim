package net.gooday2die.MIPSim.Engine;

import java.util.Hashtable;


/**
 * A Class for handing all registers
 * @author Gooday2die (Isu Kim)
 */
public class RegisterHandler {
    private Hashtable<Integer, Register> registerTable = new Hashtable<Integer, Register>();

    public static class InvalidRegisterIndex extends Exception{
        public InvalidRegisterIndex(String errorMessage){
            super(errorMessage);
        }
    }

    /**
     * A constructor method for class RegisterHandler
     * This puts every register into Hashtable
     */
    public RegisterHandler(){
       registerTable.put(0, new Register(0, "zero"));
       registerTable.put(1, new Register(0, "at"));
       registerTable.put(2, new Register(0, "v0"));
       registerTable.put(3, new Register(0, "v1"));
       registerTable.put(4, new Register(0, "a0"));
       registerTable.put(5, new Register(0, "a1"));
       registerTable.put(6, new Register(0, "a2"));
       registerTable.put(7, new Register(0, "a3"));
       registerTable.put(8, new Register(0, "t0"));
       registerTable.put(9, new Register(0, "t1"));
       registerTable.put(10, new Register(0, "t2"));
       registerTable.put(11, new Register(0, "t3"));
       registerTable.put(12, new Register(0, "t4"));
       registerTable.put(13, new Register(0, "t5"));
       registerTable.put(14, new Register(0, "t6"));
       registerTable.put(15, new Register(0, "t7"));
       registerTable.put(16, new Register(0, "s0"));
       registerTable.put(17, new Register(0, "s1"));
       registerTable.put(18, new Register(0, "s2"));
       registerTable.put(19, new Register(0, "s3"));
       registerTable.put(20, new Register(0, "s4"));
       registerTable.put(21, new Register(0, "s5"));
       registerTable.put(22, new Register(0, "s6"));
       registerTable.put(23, new Register(0, "s7"));
       registerTable.put(24, new Register(0, "t8"));
       registerTable.put(25, new Register(0, "t9"));
       registerTable.put(26, new Register(0, "k0"));
       registerTable.put(27, new Register(0, "k1"));
       registerTable.put(28, new Register(0, "gp"));
       registerTable.put(29, new Register(0, "sp"));
       registerTable.put(30, new Register(0, "fp"));
       registerTable.put(31, new Register(0, "ra"));
    }

    /**
     * A method that retrieves specific Register object from total registers
     * @param registerIndex the integer type object that represents the register's index
     * @return returns Register object that corresponds to the register
     * @throws InvalidRegisterIndex is thrown when the specified index of the register was not found.
     */
    public Register getRegister(int registerIndex) throws InvalidRegisterIndex {
        try{
            return registerTable.get(registerIndex);
        } catch(NullPointerException e){
            throw new InvalidRegisterIndex("Invalid register alias found : " + registerIndex);
        }
    }

    /**
     * A method that sets specific Register object's value from total registers
     * @param registerIndex the integer type object that represents the register's index
     * @param value the integer object to set register's value.
     */
    public void setRegister(int registerIndex, int value){
        Register r = registerTable.get(registerIndex);
        r.setValue(value);
    }

    /**
     * A getter attribute for retrieving all registers
     * @return an Hashtable object that represents all registers
     */
    public Hashtable<Integer, Register> getAllRegisters(){
        return registerTable;
    }
}

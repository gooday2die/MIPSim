package net.gooday2die.MIPSim.Engine;

import java.util.Hashtable;


/**
 * A Class for handing all registers
 * @author Gooday2die
 */
public class RegisterHandler {
    private Hashtable<String, Register> registerTable = new Hashtable<String, Register>();

    public class InvalidRegisterAlias extends Exception{
        public InvalidRegisterAlias(String errorMessage){
            super(errorMessage);
        }
    }

    /**
     * A constructor method for class RegisterHandler
     * This puts every register into Hashtable
     */
    public RegisterHandler(){
       registerTable.put("zero", new Register(0, 0));
       registerTable.put("at", new Register(0, 1));
       registerTable.put("v0", new Register(0, 2));
       registerTable.put("v1", new Register(0, 3));
       registerTable.put("a0", new Register(0, 4));
       registerTable.put("a1", new Register(0, 5));
       registerTable.put("a2", new Register(0, 6));
       registerTable.put("a3", new Register(0, 7));
       registerTable.put("t0", new Register(0, 8));
       registerTable.put("t1", new Register(0, 9));
       registerTable.put("t2", new Register(0, 10));
       registerTable.put("t3", new Register(0, 11));
       registerTable.put("t4", new Register(0, 12));
       registerTable.put("t5", new Register(0, 13));
       registerTable.put("t6", new Register(0, 14));
       registerTable.put("t7", new Register(0, 15));
       registerTable.put("s0", new Register(0, 16));
       registerTable.put("s1", new Register(0, 17));
       registerTable.put("s2", new Register(0, 18));
       registerTable.put("s3", new Register(0, 19));
       registerTable.put("s4", new Register(0, 20));
       registerTable.put("s5", new Register(0, 21));
       registerTable.put("s6", new Register(0, 22));
       registerTable.put("s7", new Register(0, 23));
       registerTable.put("t8", new Register(0, 24));
       registerTable.put("t9", new Register(0, 25));
       registerTable.put("k0", new Register(0, 26));
       registerTable.put("k1", new Register(0, 27));
       registerTable.put("gp", new Register(0, 28));
       registerTable.put("sp", new Register(0, 29));
       registerTable.put("fp", new Register(0, 30));
       registerTable.put("ra", new Register(0, 31));
    }

    /**
     * A getter method for attribute registerTable
     * @param registerAlias the String object that represents alias of register
     * @return returns Register object that corresponds to the register alias
     */
    public Register getRegister(String registerAlias) throws InvalidRegisterAlias {
        try{
            return registerTable.get(registerAlias);
        } catch(NullPointerException e){
            throw new InvalidRegisterAlias("Invalid register alias found : " + registerAlias);
        }
    }

    /**
     * A setter method for attribute registerTable
     * @param registerAlias the String object that represents alias of register
     * @param value the integer object to set register's value.
     */
    public void setRegister(String registerAlias, int value){
        Register r = registerTable.get(registerAlias);
        r.setValue(value);
    }

    /**
     * A getter attribute for retrieving all registers
     * @return an Hashtable object that represents all registers
     */
    public Hashtable<String, Register> getAllRegisters(){
        return registerTable;
    }
}

package net.gooday2die.MIPSim.Engine;

/**
 * A class for a single Register
 * @author Gooday2die (Isu Kim)
 */
public class Register {
    private int value; // the value stored in the Register
    private final int index; // the index of this Register

    /**
     * A constructor method for class Register
     * @param argValue the integer object to set default value as
     * @param argIndex the integer object to set index of this register
     */
    public Register(int argValue, int argIndex){
        value = argValue;
        index = argIndex;
    }

    /**
     * A getter method for attribute value
     * @return returns integer type object that represents stored value in this register object
     */
    public int getValue(){
        return value;
    }

    /**
     * A setter method for attribute value
     * @param argValue integer type object that represents the value to set
     */
    public void setValue(int argValue){
        value = argValue;
    }

    /**
     * A getter method for attribute index
     * @return returns integer type object that represents index of this register object.
     */
    public int getIndex(){
        return index;
    }
}

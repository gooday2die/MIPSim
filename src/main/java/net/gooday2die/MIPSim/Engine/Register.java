package net.gooday2die.MIPSim.Engine;

/**
 * A class for a single Register
 * @author Gooday2die (Isu Kim)
 */
public class Register {
    private long value; // the value stored in the Register
    private final String name; // the alias name of this Register

    /**
     * A constructor method for class Register
     * @param argValue the integer object to set default value as
     * @param argName the String object to set as alias of this register
     */
    public Register(long argValue, String argName){
        value = argValue;
        name = argName;
    }

    /**
     * A getter method for attribute value
     * @return returns integer type object that represents stored value in this register object
     */
    public long getValue(){
        return value;
    }

    /**
     * A setter method for attribute value
     * @param argValue integer type object that represents the value to set
     */
    public void setValue(long argValue){
        value = argValue;
    }

    /**
     * A getter method for attribute name
     * @return returns integer type object that represents index of this register object.
     */
    public String getName(){
        return name;
    }
}

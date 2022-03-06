package net.gooday2die.MIPSim.Parser;


/**
 * A class for storing a single expression.
 * This class stores Expression and Address of that expression as well.
 * @author Gooday2die (Isu Kim)
 */
public class Expression {
    private final String storedExpression;
    private final int storedAddress;

    /**
     * A constructor method for class Expression
     * @param expression the String type object that represents expressions
     * @param address the integer type object that represents address.
     */
    public Expression(String expression, int address){
        storedExpression = expression;
        storedAddress = address;
    }

    /**
     * A getter method for attribute storedExpression
     * @return returns String object that contains stored Expression
     */
    public String getExpression(){
        return storedExpression;
    }

    /**
     * A getter method for attribute address
     * @return returns integer object that represents the stored address of this expression
     */
    public int getAddress(){
        return storedAddress;
    }

    /**
     * A method that prints the expression and it's stored address.
     */
    public void printExpression(){
        System.out.println("Address : " + String.format("0x%08X", storedAddress) + "\nExpression : " + storedExpression);
    }
}

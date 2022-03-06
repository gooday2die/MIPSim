package net.gooday2die.MIPSim.Parser.Utils;

import java.util.Set;
import java.util.TreeSet;


/**
 * A class for checking all grammars within the expressions.
 * @author Gooday2die (Isu Kim)
 */
public class GrammarChecker {
    /**
     * An exception for when the Expression was just empty spaces or was a new line
     */
    public static class EmptyExpression extends Exception{
        public EmptyExpression(){
            super();
        }
    }

    /**
     * An exception for when the Expression was too long > 33 characters
     */
    public static class TooLongExpression extends Exception{
        public TooLongExpression(){
            super();
        }
    }

    /**
     * A method for checking if an expression was just a blank whitespaces
     * @param expressionString the String object of expression to check if it was filled with whitespaces
     * @return returns true if it was just whitespaces, false if was not
     */
    private static boolean isJustWhiteSpace(String expressionString){
        Set<Character> chars = new TreeSet<>();
        for( char c : expressionString.toCharArray() ) {
            chars.add(c);
        }
        return ((chars.size() == 1) && (chars.toArray()[0].toString().equals(" ")));
    }

    /**
     * A class for checking Basic grammar
     */
    public static class Basic{
        /**
         * A method for checking the Basic grammar
         * @param fullExpression the String object that contains the full expression
         * @return returns true if the full expression was valid, false if not
         * @throws EmptyExpression is raised when the fullExpression was just a new line or was "        "
         * @throws TooLongExpression is raised when the fullExpression's length was more than 32 characters
         */
        static boolean check(String fullExpression) throws EmptyExpression, TooLongExpression {
            if (fullExpression.length() == 0 || isJustWhiteSpace(fullExpression)) {
                // When the full expression was just an enter or if it was just a bunch of whitespaces
                // We will be raising EmptyExpression and will be skipping the current expression.
                throw new EmptyExpression();
            } else if (fullExpression.length() > 33){
                // When the full expression's length was more than 32, it was too long expression
                throw new TooLongExpression();
            } else{ // When the full expression was good in length, go check grammatical things
                return true;
            }
        }
    }

    /**
     * A class for checking R Type Grammars
     */
    public static class RType{
        /**
         * A method that checks if R Type's grammar was correct
         * For example if the full arguments were $S0, $s1, S2 this will return true
         * @param arguments String object of argument that contains the expressions.
         * @return returns true if Grammar was correct, returns false if not.
         */
        static boolean check(String arguments){
            String[] split = arguments.split(",");
            if (split.length == 3){
                for(String argument : split){ // if any of those arguments were not register
                    if (!(argument.replace(" ", "").contains("$"))) return false; // return false
                }
            }
            return true; // if all of them were registers, return true.
        }
    }

    /**
     * A class for checking I Type Grammars
     */
    public static class IType{
        ;
    }

    /**
     * A class for checking J Type Grammars
     */
    public static class JType{
        ;
    }

}

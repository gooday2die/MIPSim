package net.gooday2die.MIPSim.Engine;

import net.gooday2die.MIPSim.Engine.RegisterNames;
import net.gooday2die.MIPSim.Parser.Expression;
import net.gooday2die.MIPSim.Parser.readFile;

import java.util.ArrayList;
import java.util.List;

/**
 * A class for simulating MIPS assembly language
 * @author Gooday2die (Isu Kim)
 */
public class MIPSim {
    private int pc = 0x00000000;
    private int[] registers;
    private List<Expression> expressionList = new ArrayList<Expression>();
    private readFile rf;
    private List<String> expressionStrings;

    /**
     * A method for translating all expressionStrings into expressionList
     */
    private void generateAllExpressions() {
        for (int i = 0 ; i < expressionStrings.size() ; i++){
            Expression newExpression = new Expression(expressionStrings.get(i), pc + 4 * i);
            expressionList.add(newExpression);
            newExpression.printExpression();
        }
    }

    /**
     * A constructor method for class MIPSim
     * @param fileName the file name to read code from
     */
    public MIPSim(String fileName){
        rf = new readFile(fileName);
        registers = new int[32]; // generate 32 registers
        expressionStrings = rf.getLineList();
        generateAllExpressions();
    }

}

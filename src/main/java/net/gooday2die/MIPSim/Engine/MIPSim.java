package net.gooday2die.MIPSim.Engine;

import net.gooday2die.MIPSim.Engine.RegisterHandler;
import net.gooday2die.MIPSim.Parser.Expression;
import net.gooday2die.MIPSim.Parser.readFile;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Hashtable;
import java.util.List;

/**
 * A class for simulating MIPS assembly language
 * @author Gooday2die (Isu Kim)
 */
public class MIPSim {
    private int pc = 0x00000000;
    RegisterHandler rh;
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
    public MIPSim(String fileName) {
        rf = new readFile(fileName);
        expressionStrings = rf.getLineList();
        generateAllExpressions();
        rh = new RegisterHandler(); // generate register handler for future use

        // testing here
        try {
            System.out.println("s0 : " + rh.getRegister("s0").getValue());
            System.out.println("s1 : " + rh.getRegister("s1").getValue());
            System.out.println("s2 : " + rh.getRegister("s2").getValue());

            Instruction.addi.execute(rh.getRegister("s0"), rh.getRegister("s0"), 10);
            Instruction.addi.execute(rh.getRegister("s1"), rh.getRegister("s1"), 15);

            System.out.println("s0 : " + rh.getRegister("s0").getValue());
            System.out.println("s1 : " + rh.getRegister("s1").getValue());
            System.out.println("s2 : " + rh.getRegister("s2").getValue());

            Instruction.add.execute(rh.getRegister("s0"), rh.getRegister("s1"), rh.getRegister("s2"));

            System.out.println("s0 : " + rh.getRegister("s0").getValue());
            System.out.println("s1 : " + rh.getRegister("s1").getValue());
            System.out.println("s2 : " + rh.getRegister("s2").getValue());

        } catch (RegisterHandler.InvalidRegisterAlias e){
            System.out.println(e.getMessage());
        }
    }

}

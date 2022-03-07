package net.gooday2die.MIPSim.Engine;

import net.gooday2die.MIPSim.Engine.Instructions.InstructionActor;
import net.gooday2die.MIPSim.Engine.MachineCodes.MachineCode;
import net.gooday2die.MIPSim.Engine.MachineCodes.MachineCodeSimulator;
import net.gooday2die.MIPSim.Parser.Expression;
import net.gooday2die.MIPSim.Parser.ReadFile;

import java.util.ArrayList;
import java.util.List;

/**
 * A class for simulating MIPS assembly language
 * @author Gooday2die (Isu Kim)
 */
public class MIPSim {
    private int pc = 0x00000000;
    RegisterHandler rh;
    private List<Expression> expressionList = new ArrayList<Expression>();
    private ReadFile rf;
    private List<String> expressionStrings;
    MachineCodeSimulator mcs;
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
        rf = new ReadFile(fileName);
        expressionStrings = rf.getLineList();
        generateAllExpressions();

        rh = new RegisterHandler(); // generate register handler for future use
        mcs = new MachineCodeSimulator(rh); // generate MachineCode Simulator

        // testing here
        try {
            System.out.println("$1 : " + rh.getRegister(1).getValue());
            System.out.println("$2 : " + rh.getRegister(2).getValue());
            System.out.println("$3 : " + rh.getRegister(3).getValue());

            rh.getRegister(1).setValue(0xFFFFFFFFL);
            rh.getRegister(2).setValue(0x00000000L);

            MachineCode m1 = new MachineCode(0b00110000001000100000000000000000, 2);
            mcs.executeCode(m1);

            System.out.println("$1 : " + String.format("0x%08X", rh.getRegister(1).getValue()));
            System.out.println("$2 : " + String.format("0x%08X", rh.getRegister(2).getValue()));
            System.out.println("$3 : " + String.format("0x%08X", rh.getRegister(3).getValue()));

        }catch (Exception e){
            System.out.println(e.getMessage());
        }
    }

}

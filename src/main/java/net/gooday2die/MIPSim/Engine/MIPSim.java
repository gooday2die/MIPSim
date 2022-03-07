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
            System.out.println("$0 : " + rh.getRegister(0).getValue());
            System.out.println("$1 : " + rh.getRegister(1).getValue());
            System.out.println("$2 : " + rh.getRegister(2).getValue());

            MachineCode m1 = new MachineCode(0b00100000000000000000000000001010 ,2);
            // set register 0 as 10
            MachineCode m2 = new MachineCode(0b00100000001000010000000000001111 ,2);
            // set register 1 as 15
            MachineCode m3 = new MachineCode(0b00000000000000010001000000100000 ,1);
            // add $r0, $r1, $r3

            try {
                mcs.executeCode(m1);
                mcs.executeCode(m2);
                mcs.executeCode(m3);
            } catch (Exception e){
                System.out.println(e.getMessage());
            }

            System.out.println("$0 : " + rh.getRegister(0).getValue());
            System.out.println("$1 : " + rh.getRegister(1).getValue());
            System.out.println("$2 : " + rh.getRegister(2).getValue());

            System.out.println("$3 : " + rh.getRegister(3).getValue());
            System.out.println("$4 : " + rh.getRegister(4).getValue());

            MachineCode m4 = new MachineCode(0b00100000011000111111111111111111 ,2);
            // set register 0 as 10
            MachineCode m5 = new MachineCode(0b00100100100001001111111111111111 ,2);
            // set register 1 as 15

            try {
                mcs.executeCode(m4);
                mcs.executeCode(m5);
            } catch (Exception e){
                System.out.println(e.getMessage());
            }
            System.out.println("$3 : " + rh.getRegister(3).getValue());
            System.out.println("$4 : " + rh.getRegister(4).getValue());

            rh.getRegister(4).setValue(0xffffffff);
            MachineCode m6 = new MachineCode(0b00100100101001010000000000000001, 2);
            try {
                mcs.executeCode(m6);
            } catch (Exception e){
                System.out.println(e.getMessage());
            }
            System.out.println("=============\n$4 : " + (String.format("0x%08X", rh.getRegister(4).getValue())));
            System.out.println("$5 : " + (String.format("0x%08X", rh.getRegister(5).getValue())));
            System.out.println("$6 : " + (String.format("0x%08X", rh.getRegister(6).getValue())));

            MachineCode m7 = new MachineCode(0b00000000100001010011000000100001, 1);

            try {
                mcs.executeCode(m7);
            } catch (Exception e){
                System.out.println(e.getMessage());
            }

            System.out.println("$4 : " + (String.format("0x%08X", rh.getRegister(4).getValue())));
            System.out.println("$5 : " + (String.format("0x%08X", rh.getRegister(5).getValue())));
            System.out.println("$6 : " + (String.format("0x%08X", rh.getRegister(6).getValue())));




        } catch (RegisterHandler.InvalidRegisterIndex e){
            System.out.println(e.getMessage());
        }
    }

}

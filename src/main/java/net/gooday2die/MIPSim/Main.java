package net.gooday2die.MIPSim;

import java.io.IOException;
import java.io.InputStream;
import java.util.Properties;

public class Main {
    private static String[] mainArgs;

    /**
     * A private method for parsing args when this process was called.
     * This retrieves version from project.properties and then shows the current version of the MIPSim as well.
     */
    private static void parseArgs(){
        final Properties properties = new Properties();
        String versionString = "";

        try { // get version from project.properties
            properties.load(Main.class.getClassLoader().getResourceAsStream("project.properties"));
            versionString = properties.getProperty("version");

        } catch (IOException e){ // if resources/project.properties was not found, set it UNKNOWN
            versionString = "UNKNOWN";
        }

        System.out.println("===== MIPSim " + versionString + " By Gooday2die ====="); // show version

        if (mainArgs.length == 0) { // when there was no argument provided
            System.out.println("Error: There should be at least on arguments.");
            System.out.println("Tip: Use --help for more information.");
        } else{ // when at least one argument was provided
            switch (mainArgs[0]) {
                case "--help" -> System.out.println("Tips: lololololololol");
                case "-f", "-file" -> System.out.println("Loading file : " + mainArgs[1]);
                case "--dev" -> System.out.println("By Gooday2die @ https://github.com/gooday2die/MIPSim");
                default -> {
                    System.out.println("Error: Unknown parameter.");
                    System.out.println("Tip: Use --help for more information.");
                }
            }
        }
    }

    public static void main(String[] args){
        mainArgs = args;
        parseArgs();
    }
}

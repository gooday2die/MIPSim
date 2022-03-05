package net.gooday2die.MIPSim.Parser;


import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

import static java.lang.System.exit;

/**
 * A class for reading file line by line
 * @author Gooday2die (Isu Kim)
 */
public class readFile {
    /**
     * A constructor method for class readFile
     * @param fileName the String object that represents the file's directory
     */
    public readFile(String fileName){
        try { // Try loading the file
            FileReader fr = new FileReader(fileName);
            BufferedReader br = new BufferedReader(fr);

            String line;
            while((line = br.readLine()) != null){
                System.out.println(line);
            }

        } catch(IOException e){ // When it cannot be found, exit with error
            System.out.println("Error: Cannot locate file: " + fileName);
            exit(1); // exit with exit status 0
        }
    }
}

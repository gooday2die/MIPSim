package net.gooday2die.MIPSim.Parser;


import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.nio.file.Path;
import java.nio.file.Paths;

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
            System.out.println("Loading file : " + fileName);

            String line;
            while((line = br.readLine()) != null){
                System.out.println(line);
            }

        } catch(IOException e1){ // When it cannot be found, use relative path
            Path currentPath = Paths.get(System.getProperty("user.dir"));
            Path filePath = Paths.get(currentPath.toString(), fileName);
            System.out.println("Loading file : " + filePath);
            try { // try using relative path
                FileReader fr = new FileReader(System.getProperty(filePath.toString()));
                BufferedReader br = new BufferedReader(fr);

                String line;
                while((line = br.readLine()) != null){
                    System.out.println(line);
                }

            } catch(IOException | NullPointerException e) { // if that cannot be found as well, exit with status 1
                System.out.println("Error: Cannot locate file: " + fileName);
                exit(1); // exit with exit status 1
            }
        }
    }
}

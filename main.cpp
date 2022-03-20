#include "main.h"

#include <utility>

int main(int argc, char**argv){
    argHandler(argc, argv);
    return 0;
}

/**
 * A function that takes arguments and handles which action to perform
 * @param argc the argc
 * @param argv the argv
 */
void argHandler(int argc, char** argv) {
    if(argc == 1){
        cout << "Error: Empty arguments" << endl;
        cout << "Tip: Use --help to get information" << endl;
        exit(1);
    } else{
        queue<string> argQueue;
        commands curCommand = getCommandType(argv[1]);
        switch (curCommand) {
            case help:
                cout << "Check manual for more information!" << endl;
                break;
            case runFile: {
                if (argc < 3){
                    cout << "Error: Missing filename" << endl;
                    exit(1);
                }else if (argc == 3) {
                    cout << "Running file : " << argv[2] << endl;
                    map<string, uint32_t*> assembled = assemble(argv[2]);
                    simulate(assembled);
                }else{
                    cout << "Error: Too many filenames" << endl;
                    exit(1);
                }
                break;
            }
            case dev: {
                cout << "By Gooday2die :b" << endl;
                cout << "https://github.com/gooday2die/MIPSim" << endl;
                break;
            }
            case unknown:
                cout << "Unknown argument : " << argv[1] << endl;
                break;
        }
    }
}

/**
 * A function that takes string and turn in into which type the command was
 * @param argString the string to find type
 * @return the commands type for the command
 */
commands getCommandType(string argString){
    if(equal(argString.begin(), argString.end(), "--help")) return commands::help;
    else if (equal(argString.begin(), argString.end(), "-file")) return commands::runFile;
    else if (equal(argString.begin(), argString.end(), "-f")) return commands::runFile;
    else if (equal(argString.begin(), argString.end(), "--dev")) return commands::dev;
    else return commands::unknown;
}

/**
 * A function that takes file name string and assembles into machine codes
 * @param fileName the string that represents file name
 * @return map of string and uint32_t array;
 */
map<string, uint32_t*> assemble(const string& fileName){
    Assembler assembler = Assembler(fileName);
    return assembler.getResults();
}

/**
 * A function that simulates the machine codes.
 * @param machineCodes mapped type of string and uint32_t array that represents machine code.
 */
void simulate(const map<string, uint32_t*>& machineCodes){
    Simulator simulator = Simulator(machineCodes);
    simulator.run();
    simulator.printAllRegisters();
}
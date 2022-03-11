#include "main.h"

int main(int argc, char**argv){
    argHandler(argc, argv);
    //Assembler as = Assembler(R"(C:\Users\pc\Documents\GitHub\MIPSim\github\test.txt)");
    return 0;
}

/**
 * A function that takes arguments and handles which action to perform
 * @param argc the argc
 * @param argv the argv
 */
void argHandler(int argc, char** argv) {
    if(argc == 1){
        std::cout << "Error: Empty arguments" << std::endl;
        std::cout << "Tip: Use --help to get information" << std::endl;
        exit(1);
    } else{
        std::queue<std::string> argQueue;
        commands curCommand = getCommandType(argv[1]);
        switch (curCommand) {
            case help:
                std::cout << "Check manual for more information!" << std::endl;
                break;
            case runFile: {
                if (argc < 3){
                    std::cout << "Error: Missing filename" << std::endl;
                    exit(1);
                }else if (argc == 3) {
                    std::cout << "Running file : " << std::endl;
                    Assembler as = Assembler(argv[2]);
                }else{
                    std::cout << "Error: Too many filenames" << std::endl;
                    exit(1);
                }
                break;
            }
            case dev: {
                std::cout << "By Gooday2die :b" << std::endl;
                std::cout << "https://github.com/gooday2die/MIPSim" << std::endl;
                break;
            }
            case unknown:
                std::cout << "Unknown argument : " << argv[1] << std::endl;
                break;
        }
    }
}

/**
 * A function that takes string and turn in into which type the command was
 * @param argString the string to find type
 * @return the commands type for the command
 */
commands getCommandType(std::string argString){
    if(std::equal(argString.begin(), argString.end(), "--help")) return commands::help;
    else if (std::equal(argString.begin(), argString.end(), "-file")) return commands::runFile;
    else if (std::equal(argString.begin(), argString.end(), "-f")) return commands::runFile;
    else if (std::equal(argString.begin(), argString.end(), "--dev")) return commands::dev;
    else return commands::unknown;
}
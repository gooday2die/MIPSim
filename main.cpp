#include "main.h"

int main(int argc, char**argv){
    //argHandler(argc, argv);
    FileReader fr = FileReader(R"(C:\Users\pc\Documents\GitHub\MIPSim\github\test.txt)");
    return 0;
}


void argHandler(int argc, char** argv) {
    if(argc == 0){
        std::cout << "Error: Empty arguments" << std::endl;
        std::cout << "Tip: Use --help to get information" << std::endl;
        exit(1);
    } else{
        std::queue<std::string> argQueue;
        commands curCommand;

        for(int i = 1 ; i < argc ; i++) curCommand = getCommandType(argv[1]);
        switch (curCommand) {
            case help:
                std::cout << "Check manual for more information!" << std::endl;
                break;
            case runFile: {
                std::cout << "Running file : " << std::endl;
                FileReader fr = FileReader(R"(C:\Users\pc\Documents\GitHub\MIPSim\github\test.txt)");
                break;
            }
            case dev:
                std::cout << "" << std::endl;
                break;
        }
    }
}

commands getCommandType(std::string argString){
       if(std::strcmp(argString.c_str(), "--help") == 1) return commands::help;
       else if((std::strcmp(argString.c_str(), "-f") == 1) || ((std::strcmp(argString.c_str(), "-file")) == 1)) return commands::runFile;
       else if (std::strcmp(argString.c_str(), "-dev") == 1) return commands::dev;
}
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
            case help:{
                cout << "--help : prints out this page" << endl;
                cout << "--dev : show developer credit" << endl;
                cout << "-rf, -runfile fileName : assemble and simulate specified file" << endl;
                cout << "-a, -assemble fileName : assemble and print out the translated expressions of specified file" << endl;
            }
                break;
            case runFile: {
                if (argc < 3){
                    cout << "Error: Missing filename" << endl;
                    exit(1);
                }else if (argc == 3) {
                    map<string, uint32_t*> assembled = assemble(argv[2]);
                    simulate(assembled);
                }else{
                    cout << "Error: Too many filenames" << endl;
                    exit(1);
                }
                break;
            }
            case dev: {
                cout << R"( _____ ______   ___  ________  ________  ___  _____ ______      )" << endl;
                cout << R"(|\   _ \  _   \|\  \|\   __  \|\   ____\|\  \|\   _ \  _   \    )" << endl;
                cout << R"(\ \  \\\__\ \  \ \  \ \  \|\  \ \  \___|\ \  \ \  \\\__\ \  \   )" << endl;
                cout << R"( \ \  \\|__| \  \ \  \ \   ____\ \_____  \ \  \ \  \\|__| \  \  )" << endl;
                cout << R"(  \ \  \    \ \  \ \  \ \  \___|\|____|\  \ \  \ \  \    \ \  \ )" << endl;
                cout << R"(   \ \__\    \ \__\ \__\ \__\     ____\_\  \ \__\ \__\    \ \__\)" << endl;
                cout << R"(    \|__|     \|__|\|__|\|__|    |\_________\|__|\|__|     \|__|)" << endl;
                cout << R"(                                 \|_________|)" << endl;
                cout << "                                                    Version : " << MIPSIM_VERSION << endl;
                cout << "                                                   By Gooday2die :b" << endl;
                cout << "                               https://github.com/gooday2die/MIPSim" << endl;
                break;
            }
            case unknown:
                cout << "Unknown argument : " << argv[1] << endl;
                break;
            case assembleFile:
            {
                if (argc < 3){
                    cout << "Error: Missing filename" << endl;
                    exit(1);
                }else if (argc == 3) {
                    map<string, uint32_t*> assembled = assemble(argv[2]);
                }else{
                    cout << "Error: Too many filenames" << endl;
                    exit(1);
                }
                break;
            }
        }
    }
}

/**
 * A function that takes string and turn in into which type the command was
 * @param argString the string to find type
 * @return the commands type for the command
 */
commands getCommandType(const string& argString){
    if(argString == "--help") return commands::help;
    else if((argString == "-rf") || (argString == "-runfile")) return commands::runFile;
    else if(argString == "--dev") return commands::dev;
    else if ((argString == "-a") || (argString == "-assemble")) return commands::assembleFile;
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

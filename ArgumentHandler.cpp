//
// @file : ArgumentHandler.h
// @author : Gooday2die (Isu Kim)
// @Contacts : edina00@naver.com
// @brief : A file that implements all member functions for class ArgumentHandler
//

#include "ArgumentHandler.h"

/**
 * A constructor member function for class ArgumentHandler
 * @param argArgc the argc from main function
 * @param argArgv the argv from main function.
 */
ArgumentHandler::ArgumentHandler(int argArgc, char** argArgv) {
    this->argc = argArgc;
    this->argv = argArgv;
}

/**
 * A member function that retrieves command type from argument string
 * @param argString the argument string to look for
 * @return returns uint8_t type value that represents command types.
 */
uint8_t ArgumentHandler::getCommandType(const string& argString) {
    if(argString == "--help") return 1;
    else if((argString == "-rf") || (argString == "-runfile")) return 2;
    else if(argString == "--dev") return 3;
    else if ((argString == "-a") || (argString == "-assemble")) return 4;
    else return 5;
}

/**
 * A member function that runs the program itself
 */
void ArgumentHandler::run() {
    if(argc == 1){
        cout << "Error: Empty arguments" << endl;
        cout << "Tip: Use --help to get information" << endl;
        exit(1);
    } else{
        uint8_t commandType = this->getCommandType(this->argv[1]);
        switch (commandType) {
            case 1: {
                cout << "===== MIPSim Version : " << MIPSIM_VERSION << " by Gooday2die =====" << endl;
                cout << " --help : prints out this page" << endl;
                cout << " --dev : show developer credit" << endl;
                cout << " -rf, -runfile fileName : assemble and simulate specified file" << endl;
                cout << " -a, -assemble fileName : assemble and print out the translated expressions of specified file" << endl;
            }
                break;
            case 2: {
                if (argc < 3){
                    cout << "Error: Missing filename" << endl;
                    exit(1);
                }else if (argc == 3) {
                    MIPSim mipSim = MIPSim(argv[2]);
                    mipSim.assemble();
                    mipSim.printRegisters();
                    mipSim.simulate();
                    mipSim.printRegisters();
                    exit(0);
                }else{
                    cout << "Error: Too many filenames" << endl;
                    exit(1);
                }
            }
            case 3: {
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
            case 4: {
                if (argc < 3){
                    cout << "Error: Missing filename" << endl;
                    exit(1);
                }else if (argc == 3) {
                    MIPSim mipSim = MIPSim(argv[2]);
                    mipSim.assemble();
                    exit(0);
                }else{
                    cout << "Error: Too many filenames" << endl;
                    exit(1);
                }
                break;
            }
            default: {
                cout << "Error: Unknown Arguments" << endl;
                cout << "Use --help for information" << endl;
            }
        }
    }
}

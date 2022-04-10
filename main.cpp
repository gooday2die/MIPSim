#include "ArgumentHandler.h"

int main(int argc, char** argv) {
    ArgumentHandler argumentHandler = ArgumentHandler(argc, argv);
    argumentHandler.run();
    return 0;
}

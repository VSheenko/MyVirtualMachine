#include <iostream>
#include "AsmInterpreter.h"


int main() {
    AsmInterpreter asmInterpreter(std::make_shared<Machine>(4096));

    try {
        asmInterpreter.interpret("test");
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

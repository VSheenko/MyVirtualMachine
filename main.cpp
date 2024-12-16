#include <iostream>
#include "AsmInterpreter.h"


int main() {
    Machine machine;
    AsmInterpreter asmInterpreter(machine);

    try {
        asmInterpreter.interpret("test");
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

#include <iostream>
#include "AsmInterpreter.h"


int main(int argc, char* argv[]) {
    // 1 - asm_file
    // 2 - lof_file
    // 3 - res_file

    if (argc != 4) {
        std::cerr << "Invalid arguments count" << std::endl;
        return 1;
    }

    std::shared_ptr<Memory> memory = std::make_shared<Memory>(1024);
    std::shared_ptr<Processor> processor = std::make_shared<Processor>(memory);
    std::shared_ptr<Machine> machine = std::make_shared<Machine>(processor, memory);
    std::shared_ptr<Logger> logger = std::make_shared<Logger>(argv[2], argv[3]);
    AsmInterpreter asmInterpreter(machine, logger);



    try {
        asmInterpreter.interpret(argv[1]);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}

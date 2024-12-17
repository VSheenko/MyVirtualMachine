#include <iostream>
#include "AsmInterpreter.h"


int main() {
    std::shared_ptr<Logger> logger = std::make_shared<Logger>("logs.csv", "res.csv");
    AsmInterpreter asmInterpreter(std::make_shared<Machine>(4096), logger);

    try {
        asmInterpreter.interpret("st_test");
    } catch (std::exception& e) {
        logger->log(e.what());
        std::cerr << e.what() << std::endl;
    }
}

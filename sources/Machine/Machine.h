#ifndef MYVIRTUALMACHINE_MACHINE_H
#define MYVIRTUALMACHINE_MACHINE_H

#include <sstream>
#include "Processor/Processor.h"
#include "Memory/Memory.h"

class Machine {
private:
    Processor processor;
    Memory memory;

public:
    Machine();
    Machine(Processor& processor, Memory& memory);

    void execute(std::vector<uint8_t> code);
};


#endif //MYVIRTUALMACHINE_MACHINE_H

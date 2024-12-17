#ifndef MYVIRTUALMACHINE_MACHINE_H
#define MYVIRTUALMACHINE_MACHINE_H


#include <sstream>
#include "Processor/Processor.h"
#include "Memory/Memory.h"

class Machine {
private:
    std::shared_ptr<Processor> processor;
    std::shared_ptr<Memory> memory;
    static bool isNegativeNumber(uint32_t number);
    int32_t GetSignedNumber(uint32_t number);

public:
    Machine(uint32_t memorySize);
    Machine(std::shared_ptr<Processor> processor, std::shared_ptr<Memory> memory);

    void GetState(std::basic_ostream<char>& stream);

    void execute(std::vector<uint8_t> code);
};


#endif //MYVIRTUALMACHINE_MACHINE_H

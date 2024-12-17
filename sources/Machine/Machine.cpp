#include <iomanip>
#include <utility>
#include "Machine.h"

Machine::Machine(std::shared_ptr<Processor> processor, std::shared_ptr<Memory> memory) {
    this->processor = std::move(processor);
    this->memory = std::move(memory);
}

Machine::Machine(uint32_t memorySize) {
    memory = std::make_shared<Memory>(memorySize);
    processor = std::make_shared<Processor>(memory);
}

void Machine::execute(std::vector<uint8_t> code) {
    processor->execute(code);
}

void Machine::GetState(std::basic_ostream<char>& stream) {
    std::vector<std::pair<uint32_t, uint32_t>> memoryState;
    memory->GetState(memoryState);

    stream << "Memory state:" << std::endl;
    for (const auto&[address, value] : memoryState) {
        stream << std::hex << "[0x" << address << "] |" <<
                " " << std::setw(2) << std::setfill('0') << std::right << (uint32_t )(value & 0xff) <<
                " " << std::setw(2) << std::setfill('0') << std::right << (uint32_t )((value >> 8) & 0xff) <<
                " " << std::setw(2) << std::setfill('0') << std::right << (uint32_t )((value >> 16) & 0xff) <<
                " " << std::setw(2) << std::setfill('0') << std::right << (uint32_t )((value >> 24) & 0xff) <<
        std::endl;
    }

    std::vector<std::pair<std::string, uint32_t>> processorState;
    processor->GetRegsState(processorState);

    stream << std::endl << "Processor state:" << std::endl;
    for (const auto&[reg, value] : processorState) {
        stream << reg << "\t| 0x" << std::hex << value << std::endl;
    }
}

bool Machine::isNegativeNumber(uint32_t number) {
    return (number & 0x80000000) != 0;
}


#include "Machine.h"

Machine::Machine() : memory(Memory(4096)), processor(Processor()) {}
Machine::Machine(Processor &processor, Memory &memory): processor(processor), memory(memory) {}

void Machine::execute(std::vector<uint8_t> code) {
    processor.execute();
}

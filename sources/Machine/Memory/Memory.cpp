#include <stdexcept>
#include "Memory.h"

Memory::Memory(uint16_t size) {
    memory.resize(size);
    reset();
}


void Memory::reset() {
    std::fill(memory.begin(), memory.end(), 0);
}

std::vector<uint8_t> Memory::read(uint16_t address, uint16_t size) {
    if (address + size > memory.size()) {
        throw std::out_of_range("Memory out of bounds");
    }

    std::vector<uint8_t> res(size);
    std::copy(memory.begin() + address, memory.begin() + address + size, res.begin());

    return res;
}

void Memory::write(uint16_t address, const std::vector<uint8_t> &data) {
    if (address + data.size() > memory.size()) {
        throw std::out_of_range("Memory out of bounds");
    }

    std::copy(data.begin(), data.end(), memory.begin() + address);
}

uint16_t Memory::size() {
    return memory.size();
}

#include <stdexcept>
#include <iostream>
#include <iomanip>
#include "Memory.h"

Memory::Memory(uint16_t size) {
    std::cout << "Memory size: " << size << std::endl;
    memory = std::vector<uint8_t>(size);
    std::cout << "Memory created " << memory.size() << std::endl;
    reset();
}


void Memory::reset() {
    std::fill(memory.begin(), memory.end(), 0);
}

std::vector<uint8_t> Memory::read(uint32_t address, uint32_t size) {
    if (address + size > memory.size()) {
        throw std::out_of_range("Memory out of bounds");
    }

    std::vector<uint8_t> res(size);
    std::copy(memory.begin() + address, memory.begin() + address + size, res.begin());

    return res;
}

void Memory::write(uint32_t address, const std::vector<uint8_t>& data) {
    if (address + data.size() > memory.size()) {
        throw std::out_of_range("Memory out of bounds");
    }

    for (int i = 0; i < data.size() - 1; i++) {
        if (address - i < 0)
            break;
        if (modifiedAddresses.find(address - i) != modifiedAddresses.end())
            std::cout << std::hex << "Warning: Write [0x" << address << "] | memory address 0x" << address + i << " was modified" << std::endl;
    }

    std::copy(data.begin(), data.end(), memory.begin() + address);
    modifiedAddresses.insert(address);
}

uint32_t Memory::size() {
    return memory.size();
}

void Memory::GetState(std::vector<std::pair<uint32_t , uint32_t>> &memoryState) {
    for (auto address : modifiedAddresses) {
            memoryState.emplace_back(address, *reinterpret_cast<uint32_t*>(&memory[address]));
    }
}

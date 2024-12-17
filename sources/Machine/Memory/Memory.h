#ifndef MYVIRTUALMACHINE_MEMORY_H
#define MYVIRTUALMACHINE_MEMORY_H

#include <cstdint>
#include <vector>
#include <set>
#include <unordered_map>

class Memory {
private:
    std::vector<uint8_t> memory;
    std::set<uint32_t> modifiedAddresses;

public:
    explicit Memory(uint16_t size);
    ~Memory() = default;

    void reset();
    uint32_t size();
    void write(uint32_t address, const std::vector<uint8_t>& data);
    std::vector<uint8_t> read(uint32_t address, uint32_t size = 4);

    void GetState(std::vector<std::pair<uint32_t , uint32_t>> &memoryState);
};


#endif //MYVIRTUALMACHINE_MEMORY_H

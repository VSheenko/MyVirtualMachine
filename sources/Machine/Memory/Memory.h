#ifndef MYVIRTUALMACHINE_MEMORY_H
#define MYVIRTUALMACHINE_MEMORY_H

#include <cstdint>
#include <vector>

class Memory {
private:
    std::vector<uint8_t> memory;

public:
    explicit Memory(uint16_t size);
    ~Memory() = default;

    void reset();
    uint16_t size();
    void write(uint16_t address, const std::vector<uint8_t>& data);
    std::vector<uint8_t> read(uint16_t address, uint16_t size);
};


#endif //MYVIRTUALMACHINE_MEMORY_H

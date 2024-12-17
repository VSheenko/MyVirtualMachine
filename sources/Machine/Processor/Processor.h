#ifndef MYVIRTUALMACHINE_PROCESSOR_H
#define MYVIRTUALMACHINE_PROCESSOR_H

#include <cstdint>
#include <stack>
#include <unordered_map>
#include <functional>
#include <memory>
#include "../CommandStruct.h"
#include "Memory/Memory.h"


class Processor {
private:
    // Registers
    uint32_t ACC = 0;
    uint32_t R[8] = {0};
    void resetRegs();

    std::shared_ptr<Memory> memory;
    std::stack<uint32_t> stack;

    std::unordered_map<uint8_t, std::function<void(uint8_t, uint32_t, uint32_t)>> cmdFunMap;

    void mov    (uint8_t addrMode, uint32_t op1, uint32_t op2);
    void push   (uint8_t addrMode, uint32_t op1, uint32_t op2);
    void pop    (uint8_t addrMode, uint32_t op1, uint32_t op2);
    void xchg   (uint8_t addrMode, uint32_t op1, uint32_t op2);
    void add    (uint8_t addrMode, uint32_t op1, uint32_t op2);
    void sub    (uint8_t addrMode, uint32_t op1, uint32_t op2);
    void inc    (uint8_t addrMode, uint32_t op1, uint32_t op2);
    void dec    (uint8_t addrMode, uint32_t op1, uint32_t op2);
    void mul    (uint8_t addrMode, uint32_t op1, uint32_t op2);
    void div    (uint8_t addrMode, uint32_t op1, uint32_t op2);
    void neg    (uint8_t addrMode, uint32_t op1, uint32_t op2);
    void abs    (uint8_t addrMode, uint32_t op1, uint32_t op2);
    void and_op (uint8_t addrMode, uint32_t op1, uint32_t op2);
    void or_op  (uint8_t addrMode, uint32_t op1, uint32_t op2);
    void xor_op (uint8_t addrMode, uint32_t op1, uint32_t op2);
    void not_op (uint8_t addrMode, uint32_t op1, uint32_t op2);

    static bool isDualAddressing(uint8_t addrMode);
    uint32_t VectorToUint32(std::vector<uint8_t> vec);
public:
    explicit Processor(const std::shared_ptr<Memory>& memory);
    ~Processor() = default;

    void GetRegsState(std::vector<std::pair<std::string, uint32_t>> &regs);
    void execute(std::vector<uint8_t> code);
};


#endif //MYVIRTUALMACHINE_PROCESSOR_H

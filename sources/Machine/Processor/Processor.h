#ifndef MYVIRTUALMACHINE_PROCESSOR_H
#define MYVIRTUALMACHINE_PROCESSOR_H

#include <cstdint>
#include <stack>
#include <unordered_map>
#include "../CommandStruct.h"



class Processor {
private:
    // Registers
    uint32_t ACC = 0;
    uint32_t R[8] = {0};
    void resetRegs();

    std::stack<uint32_t> stack;
    std::unordered_map<std::string, uint8_t> opcodeMap;


    void mov(uint32_t& dst, uint32_t src);
    void push(uint32_t src);
    void pop(uint32_t& dst);
    void xchg(uint32_t& dst, uint32_t& src);
    void add(uint32_t& dst, uint32_t src);
    void sub(uint32_t& dst, uint32_t src);
    void inc(uint32_t& dst);
    void dec(uint32_t& dst);
    void mul(uint32_t& dst, uint32_t src);
    void div(uint32_t& dst, uint32_t src);
    void neg(uint32_t& dst);
public:
    Processor();
    ~Processor() = default;

    void execute(std::vector<uint8_t> code);
    void execute();

};


#endif //MYVIRTUALMACHINE_PROCESSOR_H

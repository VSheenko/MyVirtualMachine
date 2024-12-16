#ifndef MYVIRTUALMACHINE_PROCESSOR_H
#define MYVIRTUALMACHINE_PROCESSOR_H

#include <cstdint>
#include <stack>

struct regs {
    uint32_t PC = 0;
    uint32_t IR = 0;
    uint32_t ACC = 0;
    uint32_t R[8] = {0};

    uint32_t FLAGS = 0;

    void reset();
};

enum Opcode {
    MOV = 0x8A,
    PUSH = 0x50,
    POP = 0x58,
    XCHG = 0x86,

    ADD = 0x01,
    SUB = 0x2B,
    INC = 0x40,
    DEC = 0x48,
    MUL = 0xF6,
    DIV = 0xF7,
    NEG = 0xF8,

    AND = 0x21,
    OR = 0x09,
    XOR = 0x31,
    NOT = 0xF9,
};

class Processor {
private:
    std::stack<uint16_t> stack;

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

};


#endif //MYVIRTUALMACHINE_PROCESSOR_H

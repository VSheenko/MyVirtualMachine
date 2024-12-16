#include <stdexcept>
#include "Processor.h"

void regs::reset() {
    PC = 0;
    IR = 0;
    ACC = 0;

    for (uint32_t & i : R) {
        i = 0;
    }

    FLAGS = 0;
}

void Processor::mov(uint32_t& dst, uint32_t src) {

}

void Processor::push(uint32_t src) {
    stack.push(src);
}

void Processor::pop(uint32_t &dst) {
    if (stack.empty()) {
        return;
    }

    dst = stack.top();
    stack.pop();
}

void Processor::xchg(uint32_t &dst, uint32_t &src) {
    uint32_t tmp = dst;
    dst = src;
    src = tmp;
}

void Processor::add(uint32_t &dst, uint32_t src) {
    dst += src;
}

void Processor::sub(uint32_t &dst, uint32_t src) {
    dst -= src;
}

void Processor::inc(uint32_t &dst) {
    dst++;
}

void Processor::dec(uint32_t &dst) {
    dst--;
}

void Processor::mul(uint32_t &dst, uint32_t src) {
    dst *= src;
}

void Processor::div(uint32_t &dst, uint32_t src) {
    if (src == 0) {
        throw std::runtime_error("Division by zero");
    }

    dst /= src;
}

void Processor::neg(uint32_t &dst) {
    dst = -dst;
}

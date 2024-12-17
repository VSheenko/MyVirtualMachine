#include <stdexcept>
#include <sstream>
#include "Processor.h"

void Processor::execute(std::vector<uint8_t> code) {
    CommandStruct command;

    while (code.size() >= 10) {
        if (code.size() < 10) {
            throw std::runtime_error("Invalid command format");
        }

        command.SetFromBinFormat(code);
        code.erase(code.begin(), code.begin() + 10);

        if (cmdFunMap.find(command.opcode) == cmdFunMap.end()) {
            throw std::runtime_error("Unknown command");
        }

        cmdFunMap.at(command.opcode)(command.addrMode, command.operand1, command.operand2);
    }

    if (!code.empty()) {
        throw std::runtime_error("Invalid command format");
    }
}

void Processor::resetRegs() {
    ACC = 0;
    for (unsigned int & i : R) {
        i = 0;
    }
}

Processor::Processor(const std::shared_ptr<Memory>& memory) {
    this->memory = memory;
    resetRegs();

    cmdFunMap = {
            {0x8A, [this](uint8_t addrMode, uint32_t op1, uint32_t op2) { mov(addrMode, op1, op2); }},
            {0x50, [this](uint8_t addrMode, uint32_t op1, uint32_t op2) { push(addrMode, op1, op2);}},
            {0x58, [this](uint8_t addrMode, uint32_t op1, uint32_t op2) { pop(addrMode, op1, op2);}},
            {0x86, [this](uint8_t addrMode, uint32_t op1, uint32_t op2) { xchg(addrMode, op1, op2);}},
            {0x01, [this](uint8_t addrMode, uint32_t op1, uint32_t op2) { add(addrMode, op1, op2);}},
            {0x2B, [this](uint8_t addrMode, uint32_t op1, uint32_t op2) { sub(addrMode, op1, op2);}},
            {0x40, [this](uint8_t addrMode, uint32_t op1, uint32_t op2) { inc(addrMode, op1, op2);}},
            {0x48, [this](uint8_t addrMode, uint32_t op1, uint32_t op2) { dec(addrMode, op1, op2);}},
            {0xF6, [this](uint8_t addrMode, uint32_t op1, uint32_t op2) { mul(addrMode, op1, op2);}},
            {0xF7, [this](uint8_t addrMode, uint32_t op1, uint32_t op2) { div(addrMode, op1, op2);}},
            {0xFA, [this](uint8_t addrMode, uint32_t op1, uint32_t op2) { abs(addrMode, op1, op2);}},
            {0xF8, [this](uint8_t addrMode, uint32_t op1, uint32_t op2) { neg(addrMode, op1, op2);}},
            {0x21, [this](uint8_t addrMode, uint32_t op1, uint32_t op2) { and_op(addrMode, op1, op2);}},
            {0x09, [this](uint8_t addrMode, uint32_t op1, uint32_t op2) { or_op(addrMode, op1, op2);}},
            {0x31, [this](uint8_t addrMode, uint32_t op1, uint32_t op2) { xor_op(addrMode, op1, op2);}},
            {0xF9, [this](uint8_t addrMode, uint32_t op1, uint32_t op2) { not_op(addrMode, op1, op2);}}
    };


}

void Processor::mov(uint8_t addrMode, uint32_t op1, uint32_t op2) {
    if (isDualAddressing(addrMode)) {
        throw std::runtime_error("Processor::mov-> Invalid addressing mode");
    }

    uint8_t mode1 = addrMode >> 4;
    uint8_t mode2 = addrMode & 0x0F;

    if (mode1 == 0x01) {
        throw std::runtime_error("Processor::mov-> Invalid addressing mode");
    }

    uint32_t src_value = 0;
    if (mode2 == 0x01) {
        src_value = op2;
    } else if (mode2 == 0x00) {
        if (op2 == 0)
            src_value = ACC;
        else
            src_value = R[op2 - 1];
    } else if (mode2 == 0x02) {
        src_value = VectorToUint32(memory->read(op2, 4));
    } else if (mode2 == 0x03) {
        src_value = VectorToUint32(memory->read(R[op2], 4));
    }

    std::vector<uint8_t> data = {(uint8_t )((src_value) & 0xFF),
                                 (uint8_t )((src_value >> 8) & 0xFF),
                                 (uint8_t )((src_value >> 16) & 0xFF),
                                 (uint8_t )((src_value >> 24) & 0xFF)};
    if (mode1 == 0x00) {
        if (op1 == 0) {
            ACC = src_value;
        } else {
            R[op1 - 1] = src_value;
        }
    } else if (mode1 == 0x02) {
        memory->write(op1, data);
    } else if (mode1 == 0x03) {
        memory->write(R[op1], data);
    }
}

bool Processor::isDualAddressing(uint8_t addrMode) {
    return addrMode == 0x22 || addrMode == 0x33 || addrMode == 0x32 || addrMode == 0x23;
}

uint32_t Processor::VectorToUint32(std::vector<uint8_t> vec) {
    if (vec.size() != 4) {
        throw std::runtime_error("Invalid vector size");
    }

    return vec[0] | (vec[1] << 8) | (vec[2] << 16) | (vec[3] << 24);
}

void Processor::push(uint8_t addrMode, uint32_t op1, uint32_t op2) {

}

void Processor::pop(uint8_t addrMode, uint32_t op1, uint32_t op2) {

}

void Processor::xchg(uint8_t addrMode, uint32_t op1, uint32_t op2) {

}

void Processor::execute(std::vector<uint8_t> code) {
    CommandStruct command;
    command.SetFromBinFormat(code);

}

void Processor::execute() {

};

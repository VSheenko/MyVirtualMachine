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


    uint32_t src_value = GetValueByOperand(mode2, op2);
    std::vector<uint8_t> data = {(uint8_t )((src_value) & 0xFF),
                                 (uint8_t )((src_value >> 8) & 0xFF),
                                 (uint8_t )((src_value >> 16) & 0xFF),
                                 (uint8_t )((src_value >> 24) & 0xFF)};
    SetValueByOperand(mode1, op1, src_value);
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

void Processor::add(uint8_t addrMode, uint32_t op1, uint32_t op2) {

}

void Processor::execute() {

void Processor::GetRegsState(std::vector<std::pair<std::string, uint32_t>> &regs) {
    regs = {
            {"ACC", ACC},
            {"R0", R[0]},
            {"R1", R[1]},
            {"R2", R[2]},
            {"R3", R[3]},
            {"R4", R[4]},
            {"R5", R[5]},
            {"R6", R[6]},
            {"R7", R[7]}
    };
}

uint32_t Processor::GetValueByOperand(uint8_t addrMode, uint32_t operand) {
    uint32_t value = 0;

    if (addrMode == 0x01) {
        value = operand;
    } else if (addrMode == 0x00) {
        if (operand == 0) {
            value = ACC;
        } else {
            value = R[operand - 1];
        }
    } else {
        uint32_t addr = 0;
        if (addrMode == 0x02) {
            addr = operand;
        } else if (addrMode == 0x03) {
            if (operand == 0) {
                addr = ACC;
            } else {
                addr = R[operand - 1];
            }
        }

        value = VectorToUint32(memory->read(addr, 4));
    }

    return value;
}

void Processor::SetValueByOperand(uint8_t mode, uint32_t operand, uint32_t value) {
    if (mode == 0x01) {
        throw std::runtime_error("Processor-> Cannot change constant | addrMode: " + std::to_string(mode));
    }

    if (mode == 0x00) {
        if (operand == 0) {
            ACC = value;
        } else {
            R[operand - 1] = value;
        }
    } else {
        uint32_t addr = 0;
        if (mode == 0x02) {
            addr = operand;
        } else if (mode == 0x03) {
            if (operand == 0) {
                addr = ACC;
            } else {
                addr = R[operand - 1];
            }
        }

        memory->write(addr, {(uint8_t )((value) & 0xFF),
                             (uint8_t )((value >> 8) & 0xFF),
                             (uint8_t )((value >> 16) & 0xFF),
                             (uint8_t )((value >> 24) & 0xFF)});
    }
}

#include <stdexcept>
#include <regex>
#include "CommandStruct.h"

std::unordered_map<std::string, uint8_t> CommandStruct::opcodeMap = {
        {"MOV", 0x8A},
        {"PUSH", 0x50},
        {"POP", 0x58},
        {"XCHG", 0x86},

        {"ADD", 0x01},
        {"SUB", 0x2B},
        {"INC", 0x40},
        {"DEC", 0x48},
        {"MUL", 0xF6},
        {"DIV", 0xF7},
        {"ABS", 0xFA},

        {"NEG", 0xF8},
        {"AND", 0x21},
        {"OR", 0x09},
        {"XOR", 0x31},
        {"NOT", 0xF9}
};

CommandStruct::CommandStruct() : opcode(0), addrMode(0), operand1(0), operand2(0) {

}

std::vector<uint8_t> CommandStruct::GetBinFormat() const {
    std::vector<uint8_t> res;
    res.push_back(opcode);
    res.push_back(addrMode);
    res.push_back(operand1 & 0xFF);
    res.push_back((operand1 >> 8) & 0xFF);
    res.push_back((operand1 >> 16) & 0xFF);
    res.push_back((operand1 >> 24) & 0xFF);
    res.push_back(operand2 & 0xFF);
    res.push_back((operand2 >> 8) & 0xFF);
    res.push_back((operand2 >> 16) & 0xFF);
    res.push_back((operand2 >> 24) & 0xFF);
    return res;
}

void CommandStruct::SetFromBinFormat(std::vector<uint8_t> bin) {
    opcode = bin[0];
    addrMode = bin[1];
    operand1 = bin[2] | (bin[3] << 8) | (bin[4] << 16) | (bin[5] << 24);
    operand2 = bin[6] | (bin[7] << 8) | (bin[8] << 16) | (bin[9] << 24);
}

uint8_t CommandStruct::GetOpcode(std::string command) {
    if (opcodeMap.find(command) == opcodeMap.end()) {
        throw std::runtime_error("Unknown command");
    }

    return opcodeMap.at(command);
}

void CommandStruct::reset() {
    opcode = 0;
    addrMode = 0;
    operand1 = 0;
    operand2 = 0;
}

std::string CommandStruct::GetCommandName(uint8_t opcode) {
    for (const auto& [key, value] : opcodeMap) {
        if (value == opcode) {
            return key;
        }
    }

    throw std::runtime_error("Unknown opcode");
}



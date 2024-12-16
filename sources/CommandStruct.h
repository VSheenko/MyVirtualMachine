#ifndef MYVIRTUALMACHINE_COMMANDSTRUCT_H
#define MYVIRTUALMACHINE_COMMANDSTRUCT_H

#include <unordered_map>
#include <cstdint>
#include <vector>
#include <string>

struct CommandStruct {
    uint8_t opcode;
    uint8_t addrMode;
    uint32_t operand1;
    uint32_t operand2;

    CommandStruct();
    [[nodiscard]] std::vector<uint8_t> GetBinFormat() const;
    void SetFromBinFormat(std::vector<uint8_t> bin);
    static uint8_t GetOpcode(std::string command);
    static std::string GetCommandName(uint8_t opcode);
    void reset();

private:
    static std::unordered_map<std::string, uint8_t> opcodeMap;
};

#endif //MYVIRTUALMACHINE_COMMANDSTRUCT_H

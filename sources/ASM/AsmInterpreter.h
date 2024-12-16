#ifndef MYVIRTUALMACHINE_ASMINTERPRETER_H
#define MYVIRTUALMACHINE_ASMINTERPRETER_H


#include <cstdint>
#include <filesystem>
#include <unordered_map>
#include "Machine.h"
#include "../CommandStruct.h"

class AsmInterpreter {
private:
    Machine machine;

    void executeCommand(CommandStruct& command);
    static uint8_t GetAddrMode(const std::string& operand);
    static uint32_t GetOperandValue(const std::string& operand);
    static void ParseCommand(const std::string& command, CommandStruct& commandStruct);
public:
    explicit AsmInterpreter(Machine& machine);
    void interpret(const std::filesystem::path& asmFilePath);

};


#endif //MYVIRTUALMACHINE_ASMINTERPRETER_H

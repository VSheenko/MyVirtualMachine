#ifndef MYVIRTUALMACHINE_ASMINTERPRETER_H
#define MYVIRTUALMACHINE_ASMINTERPRETER_H


#include <cstdint>
#include <filesystem>
#include <unordered_map>
#include "Machine.h"
#include "../CommandStruct.h"
#include "../Logger/Logger.h"

class AsmInterpreter {
private:
    std::shared_ptr<Machine> machine;
    std::shared_ptr<Logger> logger;

    void executeCommand(CommandStruct& command);
    static uint8_t GetAddrMode(const std::string& operand);
    static uint32_t GetOperandValue(const std::string& operand);
    static void ParseCommand(const std::string& command, CommandStruct& commandStruct);
    void LogCommand(const CommandStruct& command);
public:
    explicit AsmInterpreter(std::shared_ptr<Machine> machine, std::shared_ptr<Logger> logger);
    void interpret(const std::filesystem::path& asmFilePath);

};


#endif //MYVIRTUALMACHINE_ASMINTERPRETER_H

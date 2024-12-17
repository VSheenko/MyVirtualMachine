#include <fstream>
#include <iostream>
#include <regex>
#include <algorithm>
#include "AsmInterpreter.h"


AsmInterpreter::AsmInterpreter(std::shared_ptr<Machine> machine, std::shared_ptr<Logger> logger) {
    this->machine = std::move(machine);
    this->logger = std::move(logger);
}

void AsmInterpreter::interpret(const std::filesystem::path& asmFilePath) {
    if (!std::filesystem::exists(asmFilePath)) {
        throw std::runtime_error("File not found");
    }

    std::fstream file(asmFilePath, std::ios::in);
    if (!file.is_open()) {
        throw std::runtime_error("Can't open file");
    }

    std::string line;
    CommandStruct command;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        ParseCommand(line, command);
        LogCommand(command);
        executeCommand(command);
    }

    file.close();
    machine->GetState(std::cout);
}

void AsmInterpreter::ParseCommand(const std::string& command, CommandStruct& commandStruct) {
    commandStruct.reset();

    std::vector<std::string> operands;

    std::smatch matches;
    std::regex asmRegex(R"(^\s*([A-Za-z]+)\s*(.*)\s*$)");
    if (std::regex_match(command, matches, asmRegex)) {
        std::string cmd = matches[1];
        std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::toupper);

        commandStruct.opcode = CommandStruct::GetOpcode(cmd);  // Первая группа - команда
        std::string operandsStr = matches[2];  // Вторая группа - операнды

        size_t start = 0;
        size_t end = operandsStr.find(',');
        while (end != std::string::npos) {
            operands.push_back(operandsStr.substr(start, end - start));
            start = end + 1;
            end = operandsStr.find(',', start);
        }

        operands.push_back(operandsStr.substr(start));
    } else {
        throw std::runtime_error("AsmInterpreter::ParseCommand-> Invalid command format: " + command);
    }

    if (operands.size() == 2) {
        uint8_t mode1 = GetAddrMode(operands[0]);
        uint8_t mode2 = GetAddrMode(operands[1]);

        commandStruct.addrMode = 0 | (mode1 << 4) | mode2;

        commandStruct.operand1 = GetOperandValue(operands[0]);
        commandStruct.operand2 = GetOperandValue(operands[1]);
        return;
    } else if (operands.size() == 1) {
        uint8_t mode1 = GetAddrMode(operands[0]);
        commandStruct.addrMode = 0 | (mode1 << 4) | 0xF;

        commandStruct.operand1 = GetOperandValue(operands[0]);
        commandStruct.operand2 = 0;
        return;
    }

    throw std::runtime_error("AsmInterpreter::ParseCommand-> Invalid operands count");
}

void AsmInterpreter::executeCommand(CommandStruct &command) {
    machine->execute(command.GetBinFormat());
}

uint8_t AsmInterpreter::GetAddrMode(const std::string &operand) {
    std::regex addrRegex(R"(^\[(0x[0-9A-Fa-f]+|\d+)\]$)");
    std::regex regRegex(R"(^(R[0-7]|ACC)$)");
    std::regex regAddrRegex(R"(^\[(R[0-7]|ACC)\]$)");
    std::regex numRegex(R"(^(-?\d+|0x[0-9A-Fa-f]+)$)");


    std::string cleaned = operand;
    cleaned.erase(0, cleaned.find_first_not_of(" \t"));
    cleaned.erase(cleaned.find_last_not_of(" \t") + 1);

    if (std::regex_match(cleaned, addrRegex)) {
        return 2;
    } else if (std::regex_match(cleaned, regRegex)) {
        return 0;
    } else if (std::regex_match(cleaned, regAddrRegex)) {
        return 3;
    } else if (std::regex_match(cleaned, numRegex)) {
        return 1;
    } else {
        throw std::runtime_error("Invalid operand format");
    }
}

uint32_t AsmInterpreter::GetOperandValue(const std::string &operand) {
    std::string cleaned = operand;
    cleaned.erase(0, cleaned.find_first_not_of(" \t"));
    cleaned.erase(cleaned.find_last_not_of(" \t") + 1);

    if (cleaned.size() >= 2 && cleaned.front() == '[' && cleaned.back() == ']') {
        cleaned = cleaned.substr(1, cleaned.size() - 2);
    }

    if (cleaned.front() == 'R') {
        uint32_t res = 1 + std::stoul(cleaned.substr(1));
        if (res > 8) {
            throw std::runtime_error("Invalid register number");
        }
        return res;
    } else if (cleaned == "ACC") {
        return 0;
    } else if (cleaned.front() == '0' && cleaned[1] == 'x') {
        return std::stoul(cleaned, nullptr, 16);
    } else {
        return std::stoul(cleaned);
    }
}

void AsmInterpreter::LogCommand(const CommandStruct &command) {
    char separator = ',';
    std::string logMessage = CommandStruct::GetCommandName(command.opcode) + separator;
    int32_t value1 = (command.operand1 & 0x80000000) != 0 ? -1 * (int32_t) ((~command.operand1 + 1) & 0x7FFFFFFF) : command.operand1;
    int32_t value2 = (command.operand2 & 0x80000000) != 0 ? -1 * (int32_t) ((~command.operand2 + 1) & 0x7FFFFFFF) : command.operand2;

    logMessage += std::to_string(value1) + separator;
    logMessage += std::to_string(value2);

    logger->log(logMessage);

    std::vector<uint8_t> binFormat = command.GetBinFormat();
    std::string binStr;
    for (int i = 0; i < binFormat.size(); i++) {
        binStr += std::bitset<8>(binFormat[i]).to_string();
        if (i != binFormat.size() - 1) {
            binStr += separator;
        }
    }

    logger->toResFile(binStr);
}


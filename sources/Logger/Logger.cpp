#include <fstream>
#include "Logger.h"

Logger::Logger(std::filesystem::path logFilePath, std::filesystem::path resFile) {
    if (!std::filesystem::exists(logFilePath)) {
        throw std::runtime_error("Log file not found");
    }
    if (!std::filesystem::exists(resFile)) {
        throw std::runtime_error("Result file not found");
    }

    this->logFilePath = std::move(logFilePath);

    std::ofstream file(this->logFilePath);
    if (!file.is_open()) {
        throw std::runtime_error("Can't open log file");
    }
    file << "Command,Operand1,Operand2" << std::endl;
    file.close();

    this->resFile = std::move(resFile);
    std::ofstream file_res(this->resFile);
    if (!file_res.is_open()) {
        throw std::runtime_error("Can't open res file");
    }
    file_res.close();
}

void Logger::log(const std::string &message) {
    std::ofstream file(logFilePath, std::ios::app);
    if (!file.is_open()) {
        throw std::runtime_error("Can't open log file");
    }

    file << message << std::endl;
    file.close();
}

void Logger::toResFile(const std::string &message) {
    std::ofstream file(resFile, std::ios::app);
    if (!file.is_open()) {
        throw std::runtime_error("Can't open log file");
    }

    file << message << std::endl;
    file.close();
}
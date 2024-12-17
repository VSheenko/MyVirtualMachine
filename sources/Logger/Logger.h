#ifndef MYVIRTUALMACHINE_LOGGER_H
#define MYVIRTUALMACHINE_LOGGER_H

#include <filesystem>


class Logger {
private:
    std::filesystem::path logFilePath;
    std::filesystem::path resFile;
public:
    explicit Logger(std::filesystem::path logFilePath, std::filesystem::path resFile);
    void log(const std::string& message);
    void toResFile(const std::string& message);
};


#endif //MYVIRTUALMACHINE_LOGGER_H

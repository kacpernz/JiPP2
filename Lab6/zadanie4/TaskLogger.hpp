#pragma once
#include <string>
#include <cstdint>
#include <ctime>

struct LogRecord {
    time_t timestamp;
    char taskName[64];
    bool success;
    int errorCode; // 0 = Brak błędu, 1 = Math, 2 = File, 3 = Format, 4 = Inny
};

class TaskLogger {
public:
    explicit TaskLogger(const std::string& logFilePath);
    void log(const std::string& taskName, bool success, int errorCode = 0);
    void printHistory() const;

private:
    std::string path;
};
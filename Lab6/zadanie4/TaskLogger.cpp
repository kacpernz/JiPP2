#include "TaskLogger.hpp"
#include <fstream>
#include <iostream>
#include <cstring>

TaskLogger::TaskLogger(const std::string& logFilePath) : path(logFilePath) {}

void TaskLogger::log(const std::string& taskName, bool success, int errorCode) {
    std::ofstream file(path, std::ios::binary | std::ios::app);
    if (!file) return; 

    LogRecord record{};
    record.timestamp = std::time(nullptr);
    std::strncpy(record.taskName, taskName.c_str(), sizeof(record.taskName) - 1);
    record.taskName[sizeof(record.taskName) - 1] = '\0';
    record.success = success;
    record.errorCode = errorCode;

    file.write(reinterpret_cast<const char*>(&record), sizeof(LogRecord));
}

void TaskLogger::printHistory() const {
    std::ifstream file(path, std::ios::binary);
    if (!file) {
        std::cout << "Brak historii logow.\n";
        return;
    }

    LogRecord record;
    std::cout << "\n--- Historia Uruchomien Taskow ---\n";
    while (file.read(reinterpret_cast<char*>(&record), sizeof(LogRecord))) {
        char timeStr[26];
        #ifdef _MSC_VER
            ctime_s(timeStr, sizeof(timeStr), &record.timestamp);
        #else
            ctime_r(&record.timestamp, timeStr);
        #endif
        timeStr[24] = '\0'; 

        std::cout << "[" << timeStr << "] " << record.taskName 
                  << " | Status: " << (record.success ? "SUKCES" : "BLAD") 
                  << " | Kod Bledu: " << record.errorCode << '\n';
    }
}
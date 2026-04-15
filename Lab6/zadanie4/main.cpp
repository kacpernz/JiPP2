#include "Executor.hpp"
#include "TaskLogger.hpp"
#include <iostream>
#include <fstream>

void createTestBinaryFile(const std::string& path) {
    std::ofstream file(path, std::ios::binary);
    double values[] = { 10.5, 20.0, 5.5, 4.0 };
    file.write(reinterpret_cast<const char*>(values), sizeof(values));
}

void createCorruptedBinaryFile(const std::string& path) {
    std::ofstream file(path, std::ios::binary);
    char badData[] = "To_nie_sa_double_i_dlugosc_sie_nie_zgadza";
    file.write(badData, sizeof(badData));
}

int main() {
    TaskLogger logger("task_history.bin");

    createTestBinaryFile("dane.bin");
    createCorruptedBinaryFile("bad_dane.bin");

    Executor executor;
    
    executor.addTask(std::make_unique<DivideTask>(10.0, 2.0));
    executor.addTask(std::make_unique<SqrtTask>(16.0));
    executor.addTask(std::make_unique<FileSizeTask>("dane.bin"));
    executor.addTask(std::make_unique<MeanFromBinaryFileTask>("dane.bin"));
    
    executor.addTask(std::make_unique<DivideTask>(5.0, 0.0));
    executor.addTask(std::make_unique<SqrtTask>(-9.0));
    executor.addTask(std::make_unique<FileSizeTask>("brak.bin"));
    executor.addTask(std::make_unique<MeanFromBinaryFileTask>("bad_dane.bin")); 

    executor.runAll(logger);

    logger.printHistory();

    return 0;
}
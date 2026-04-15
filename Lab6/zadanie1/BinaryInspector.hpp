#pragma once
#include <string>
#include <cstdint>

class BinaryInspector {
public:
    explicit BinaryInspector(const std::string& filePath);

    void printFileSize();
    void printFirst64Bytes();
    void printByteHistogram();
    void readValue(uint64_t offset, const std::string& type);

private:
    std::string path;
    uint64_t getFileSize();

    template<typename T>
    T readAtOffset(uint64_t offset);
};
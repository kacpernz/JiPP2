#include "BinaryInspector.hpp"
#include "Exceptions.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <cctype>

BinaryInspector::BinaryInspector(const std::string& filePath) : path(filePath) {
    std::ifstream file(path, std::ios::binary | std::ios::ate);
    if (!file) {
        throw std::runtime_error("Nie udalo sie otworzyc pliku: " + path);
    }
}

uint64_t BinaryInspector::getFileSize() {
    std::ifstream file(path, std::ios::binary | std::ios::ate);
    if (!file) throw std::runtime_error("Blad odczytu pliku.");
    return static_cast<uint64_t>(file.tellg());
}

void BinaryInspector::printFileSize() {
    std::cout << "Rozmiar pliku: " << getFileSize() << " bajtow\n";
}

void BinaryInspector::printFirst64Bytes() {
    std::ifstream file(path, std::ios::binary);
    if (!file) throw std::runtime_error("Blad odczytu pliku.");

    const int bytesToRead = 64;
    std::vector<unsigned char> buffer(bytesToRead, 0);
    
    file.read(reinterpret_cast<char*>(buffer.data()), bytesToRead);
    std::streamsize bytesRead = file.gcount();

    std::cout << "Pierwsze " << bytesRead << " bajtow:\n";
    for (std::streamsize i = 0; i < bytesRead; i += 16) {
        for (std::streamsize j = 0; j < 16; ++j) {
            if (i + j < bytesRead) {
                std::cout << std::hex << std::setw(2) << std::setfill('0') 
                          << static_cast<int>(buffer[i + j]) << " ";
            } else {
                std::cout << "   ";
            }
        }
        
        std::cout << " | ";
        
        for (std::streamsize j = 0; j < 16 && (i + j) < bytesRead; ++j) {
            unsigned char c = buffer[i + j];
            if (std::isprint(c)) {
                std::cout << c;
            } else {
                std::cout << '.';
            }
        }
        std::cout << '\n';
    }
    std::cout << std::dec;
}

void BinaryInspector::printByteHistogram() {
    std::ifstream file(path, std::ios::binary);
    if (!file) throw std::runtime_error("Blad odczytu pliku.");

    std::vector<uint64_t> histogram(256, 0);
    char buffer[4096];

    while (file.read(buffer, sizeof(buffer))) {
        for (std::streamsize i = 0; i < file.gcount(); ++i) {
            histogram[static_cast<unsigned char>(buffer[i])]++;
        }
    }
    
    for (std::streamsize i = 0; i < file.gcount(); ++i) {
        histogram[static_cast<unsigned char>(buffer[i])]++;
    }

    std::cout << "\nHistogram bajtow:\n";
    for (int i = 0; i < 256; ++i) {
        if (histogram[i] > 0) {
            std::cout << "0x" << std::hex << std::setw(2) << std::setfill('0') << i << std::dec 
                      << " : " << histogram[i] << " razy\n";
        }
    }
}

template<typename T>
T BinaryInspector::readAtOffset(uint64_t offset) {
    uint64_t fSize = getFileSize();
    if (offset + sizeof(T) > fSize) {
        throw BinaryRangeException("Offset wychodzi poza zakres pliku!");
    }

    std::ifstream file(path, std::ios::binary);
    file.seekg(offset, std::ios::beg);
    
    T value;
    file.read(reinterpret_cast<char*>(&value), sizeof(T));
    return value;
}

void BinaryInspector::readValue(uint64_t offset, const std::string& type) {
    std::cout << "\nWartosc pod offsetem " << offset << " (" << type << "): ";
    try {
        if (type == "u16") {
            std::cout << readAtOffset<uint16_t>(offset) << '\n';
        } else if (type == "u32") {
            std::cout << readAtOffset<uint32_t>(offset) << '\n';
        } else if (type == "u64") {
            std::cout << readAtOffset<uint64_t>(offset) << '\n';
        } else {
            throw std::invalid_argument("Nieznany typ. Uzyj: u16, u32 lub u64.");
        }
    } catch (const BinaryRangeException& e) {
        std::cerr << "Blad zakresu: " << e.what() << '\n';
    }
}
#include "BinaryInspector.hpp"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Uzycie: " << argv[0] << " <plik_binarny> [--offset N --type u16|u32|u64]\n";
        return 1;
    }

    std::string filePath = argv[1];
    uint64_t offset = 0;
    std::string type = "";
    bool readSpecificValue = false;

    for (int i = 2; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--offset" && i + 1 < argc) {
            offset = std::stoull(argv[++i]);
            readSpecificValue = true;
        } else if (arg == "--type" && i + 1 < argc) {
            type = argv[++i];
        }
    }

    try {
        BinaryInspector inspector(filePath);
        inspector.printFileSize();
        inspector.printFirst64Bytes();
        inspector.printByteHistogram();

        if (readSpecificValue && !type.empty()) {
            inspector.readValue(offset, type);
        } else if (readSpecificValue) {
            std::cerr << "Podano offset, ale nie podano typu! Uzyj --type u16|u32|u64\n";
        }

    } catch (const std::exception& e) {
        std::cerr << "Wyjatek: " << e.what() << '\n';
        return 1;
    }

    return 0;
}
#pragma once
#include <stdexcept>
#include <string>

class BinaryRangeException : public std::out_of_range {
public:
    explicit BinaryRangeException(const std::string& message) 
        : std::out_of_range(message) {}
};
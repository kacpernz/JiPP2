#pragma once
#include <stdexcept>
#include <string>

class UnknownTypeException : public std::runtime_error {
public:
    explicit UnknownTypeException(const std::string& message) 
        : std::runtime_error(message) {}
};
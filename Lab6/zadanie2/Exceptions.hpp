#pragma once
#include <stdexcept>
#include <string>

class DatabaseFormatException : public std::runtime_error {
public:
    explicit DatabaseFormatException(const std::string& message) 
        : std::runtime_error(message) {}
};

class DuplicateRecordException : public std::logic_error {
public:
    explicit DuplicateRecordException(const std::string& message) 
        : std::logic_error(message) {}
};
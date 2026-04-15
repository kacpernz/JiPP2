#pragma once
#include <stdexcept>
#include <string>

class TaskException : public std::runtime_error {
public:
    explicit TaskException(const std::string& message) : std::runtime_error(message) {}
};

class MathException : public TaskException {
public:
    explicit MathException(const std::string& message) : TaskException(message) {}
};

class FileException : public TaskException {
public:
    explicit FileException(const std::string& message) : TaskException(message) {}
};

class FormatException : public TaskException {
public:
    explicit FormatException(const std::string& message) : TaskException(message) {}
};
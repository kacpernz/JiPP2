#pragma once
#include <string>
#include <vector>

class Task {
public:
    virtual ~Task() = default; 
    virtual std::string name() const = 0;
    virtual double run() const = 0;
};

class DivideTask : public Task {
    double a, b;
public:
    DivideTask(double a, double b);
    std::string name() const override;
    double run() const override;
};

class SqrtTask : public Task {
    double x;
public:
    explicit SqrtTask(double x);
    std::string name() const override;
    double run() const override;
};

class FileSizeTask : public Task {
    std::string path;
public:
    explicit FileSizeTask(const std::string& path);
    std::string name() const override;
    double run() const override;
};

class MeanFromBinaryFileTask : public Task {
    std::string path;
    double calculateMean() const; 
public:
    explicit MeanFromBinaryFileTask(const std::string& path);
    std::string name() const override;
    double run() const override;
};
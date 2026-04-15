#include "Tasks.hpp"
#include "Exceptions.hpp"
#include <cmath>
#include <fstream>
#include <iostream>

// DivideTask 
DivideTask::DivideTask(double a, double b) : a(a), b(b) {}
std::string DivideTask::name() const { return "DivideTask(" + std::to_string(a) + " / " + std::to_string(b) + ")"; }
double DivideTask::run() const {
    if (b == 0.0) throw MathException("Dzielenie przez zero!");
    return a / b;
}

// SqrtTask 
SqrtTask::SqrtTask(double x) : x(x) {}
std::string SqrtTask::name() const { return "SqrtTask(" + std::to_string(x) + ")"; }
double SqrtTask::run() const {
    if (x < 0.0) throw MathException("Pierwiastek z liczby ujemnej!");
    return std::sqrt(x);
}

// FileSizeTask 
FileSizeTask::FileSizeTask(const std::string& path) : path(path) {}
std::string FileSizeTask::name() const { return "FileSizeTask(" + path + ")"; }
double FileSizeTask::run() const {
    std::ifstream file(path, std::ios::binary | std::ios::ate);
    if (!file) throw FileException("Nie znaleziono pliku do sprawdzenia rozmiaru: " + path);
    return static_cast<double>(file.tellg());
}

// MeanFromBinaryFileTask 
MeanFromBinaryFileTask::MeanFromBinaryFileTask(const std::string& path) : path(path) {}
std::string MeanFromBinaryFileTask::name() const { return "MeanFromBinaryFileTask(" + path + ")"; }

double MeanFromBinaryFileTask::calculateMean() const {
    std::ifstream file(path, std::ios::binary | std::ios::ate);
    if (!file) throw FileException("Brak pliku do obliczenia sredniej: " + path);

    std::streamsize size = file.tellg();
    if (size == 0) throw FormatException("Plik jest pusty.");
    if (size % sizeof(double) != 0) throw FormatException("Rozmiar pliku nie jest wielokrotnoscia double.");

    file.seekg(0, std::ios::beg);
    double sum = 0.0;
    double val;
    size_t count = 0;

    while (file.read(reinterpret_cast<char*>(&val), sizeof(double))) {
        sum += val;
        count++;
    }
    return sum / count;
}

double MeanFromBinaryFileTask::run() const {
    try {
        return calculateMean();
    } 
    catch (const FormatException& e) {
        std::cerr << "[Log wewnetrzny Taska] Zlapano blad formatu. Przekazuje wyzej...\n";
        throw;
    }
}
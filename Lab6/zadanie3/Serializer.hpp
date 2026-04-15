#pragma once
#include "Shapes.hpp"
#include <string>
#include <vector>
#include <memory>
#include <fstream>

class Serializer {
public:
    static void saveToFile(const std::string& filename, const std::vector<std::unique_ptr<Shape>>& shapes);
    static std::vector<std::unique_ptr<Shape>> loadFromFile(const std::string& filename);

private:
    static void writeShape(std::ofstream& out, const Shape* shape);
    static std::unique_ptr<Shape> readShape(std::ifstream& in);
};
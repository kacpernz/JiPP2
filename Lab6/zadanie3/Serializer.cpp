#include "Serializer.hpp"
#include "Exceptions.hpp"
#include <typeinfo>
#include <iostream>

void Serializer::saveToFile(const std::string& filename, const std::vector<std::unique_ptr<Shape>>& shapes) {
    std::ofstream out(filename, std::ios::binary | std::ios::trunc);
    if (!out) throw std::runtime_error("Nie udalo sie otworzyc pliku do zapisu.");

    size_t count = shapes.size();
    out.write(reinterpret_cast<const char*>(&count), sizeof(count));

    for (const auto& shape : shapes) {
        writeShape(out, shape.get());
    }
}

std::vector<std::unique_ptr<Shape>> Serializer::loadFromFile(const std::string& filename) {
    std::ifstream in(filename, std::ios::binary);
    if (!in) throw std::runtime_error("Nie udalo sie otworzyc pliku do odczytu.");

    size_t count = 0;
    if (!in.read(reinterpret_cast<char*>(&count), sizeof(count))) {
        return {}; 
    }

    std::vector<std::unique_ptr<Shape>> shapes;
    for (size_t i = 0; i < count; ++i) {
        shapes.push_back(readShape(in));
    }
    return shapes;
}

void Serializer::writeShape(std::ofstream& out, const Shape* shape) {
    if (!shape) return;

    std::string typeName = typeid(*shape).name();
    size_t nameLen = typeName.size();
    out.write(reinterpret_cast<const char*>(&nameLen), sizeof(nameLen));
    out.write(typeName.c_str(), nameLen);

    if (auto c = dynamic_cast<const Circle*>(shape)) {
        double r = c->getRadius();
        out.write(reinterpret_cast<const char*>(&r), sizeof(r));
    } 
    else if (auto r = dynamic_cast<const Rectangle*>(shape)) {
        double w = r->getWidth(), h = r->getHeight();
        out.write(reinterpret_cast<const char*>(&w), sizeof(w));
        out.write(reinterpret_cast<const char*>(&h), sizeof(h));
    } 
    else if (auto t = dynamic_cast<const Triangle*>(shape)) {
        double b = t->getBase(), h = t->getHeight();
        out.write(reinterpret_cast<const char*>(&b), sizeof(b));
        out.write(reinterpret_cast<const char*>(&h), sizeof(h));
    } 
    else if (auto g = dynamic_cast<const Group*>(shape)) {
        const auto& children = g->getShapes();
        size_t count = children.size();
        out.write(reinterpret_cast<const char*>(&count), sizeof(count));
        for (const auto& child : children) {
            writeShape(out, child.get()); 
        }
    } 
    else {
        throw std::logic_error("Proba zapisu niezbadanego typu dziedziczacego po Shape.");
    }
}

std::unique_ptr<Shape> Serializer::readShape(std::ifstream& in) {
    size_t nameLen = 0;
    if (!in.read(reinterpret_cast<char*>(&nameLen), sizeof(nameLen))) {
        throw std::runtime_error("Blad odczytu z pliku (oczekiwano nazwy typu).");
    }

    std::string typeName(nameLen, '\0');
    in.read(&typeName[0], nameLen);

    if (typeName == typeid(Circle).name()) {
        double r;
        in.read(reinterpret_cast<char*>(&r), sizeof(r));
        return std::make_unique<Circle>(r);
    } 
    else if (typeName == typeid(Rectangle).name()) {
        double w, h;
        in.read(reinterpret_cast<char*>(&w), sizeof(w));
        in.read(reinterpret_cast<char*>(&h), sizeof(h));
        return std::make_unique<Rectangle>(w, h);
    } 
    else if (typeName == typeid(Triangle).name()) {
        double b, h;
        in.read(reinterpret_cast<char*>(&b), sizeof(b));
        in.read(reinterpret_cast<char*>(&h), sizeof(h));
        return std::make_unique<Triangle>(b, h);
    } 
    else if (typeName == typeid(Group).name()) {
        auto g = std::make_unique<Group>();
        size_t count;
        in.read(reinterpret_cast<char*>(&count), sizeof(count));
        for (size_t i = 0; i < count; ++i) {
            g->addShape(readShape(in)); // Odczyt rekurencyjny
        }
        return g;
    } 

    throw UnknownTypeException("Nieznany identyfikator typu w pliku: " + typeName);
}
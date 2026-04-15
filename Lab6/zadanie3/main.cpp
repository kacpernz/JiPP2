#include "Shapes.hpp"
#include "Serializer.hpp"
#include <iostream>
#include <vector>

void printShapes(const std::vector<std::unique_ptr<Shape>>& shapes, int indent = 0) {
    std::string prefix(indent, ' ');
    for (const auto& shape : shapes) {
        if (auto g = dynamic_cast<const Group*>(shape.get())) {
            std::cout << prefix << "[Group] Total Area: " << g->area() << '\n';
            printShapes(g->getShapes(), indent + 4);
        } else {
            const Shape* rawShape = shape.get(); 
            std::cout << prefix << "- " << typeid(*rawShape).name() 
                      << " Area: " << shape->area() << '\n';
        }
    }
}

int main() {
    std::string filename = "shapes.bin";

    try {
        std::vector<std::unique_ptr<Shape>> shapesToSave;
        
        shapesToSave.push_back(std::make_unique<Circle>(5.0));
        shapesToSave.push_back(std::make_unique<Rectangle>(4.0, 5.0));

        auto group = std::make_unique<Group>();
        group->addShape(std::make_unique<Triangle>(3.0, 4.0));
        group->addShape(std::make_unique<Circle>(2.0));
        
        shapesToSave.push_back(std::move(group));

        std::cout << "--- Przed zapisem ---\n";
        printShapes(shapesToSave);

        Serializer::saveToFile(filename, shapesToSave);
        std::cout << "\nZapisano do pliku binarnego: " << filename << "\n";

        auto loadedShapes = Serializer::loadFromFile(filename);
        std::cout << "\n--- Po odczycie z pliku ---\n";
        printShapes(loadedShapes);

    } catch (const std::exception& e) {
        std::cerr << "Wystapil blad: " << e.what() << '\n';
    }

    return 0;
}
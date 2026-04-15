#include "Shapes.hpp"

// Circle
Circle::Circle(double r) : radius(r) {}
double Circle::area() const { return 3.1415926535 * radius * radius; }
double Circle::getRadius() const { return radius; }

// Rectangle
Rectangle::Rectangle(double w, double h) : width(w), height(h) {}
double Rectangle::area() const { return width * height; }
double Rectangle::getWidth() const { return width; }
double Rectangle::getHeight() const { return height; }

// Triangle
Triangle::Triangle(double b, double h) : base(b), height(h) {}
double Triangle::area() const { return 0.5 * base * height; }
double Triangle::getBase() const { return base; }
double Triangle::getHeight() const { return height; }

// Group 
void Group::addShape(std::unique_ptr<Shape> shape) {
    if (shape) {
        shapes.push_back(std::move(shape));
    }
}
double Group::area() const {
    double totalArea = 0.0;
    for (const auto& shape : shapes) {
        totalArea += shape->area();
    }
    return totalArea;
}
const std::vector<std::unique_ptr<Shape>>& Group::getShapes() const {
    return shapes;
}
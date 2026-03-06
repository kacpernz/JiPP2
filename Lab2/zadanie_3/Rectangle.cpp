#include "Rectangle.hpp"

Rectangle::Rectangle(double width, double height) 
    : width(width), height(height) {
}

double Rectangle::area() const {
    return width * height;
}

double Rectangle::perimeter() const {
    return 2 * (width + height);
}

bool Rectangle::isSquare() const {
    return width == height;
}

void Rectangle::scale(double factor) {
    if (factor > 0.0) {
        width *= factor;
        height *= factor;
    }
}

Rectangle Rectangle::createSquare(double side) {
    return Rectangle(side, side);
}
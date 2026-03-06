#include <iostream>
#include "Rectangle.hpp"

int main() {
    Rectangle rect(4.0, 5.0);
    std::cout << "Pole prostokata: " << rect.area() << "\n";
    std::cout << "Obwod prostokata: " << rect.perimeter() << "\n";
    
    std::cout << "Czy kwadrat? " << (rect.isSquare() ? "Tak" : "Nie") << "\n";

    rect.scale(2.0);
    std::cout << "\nPo skalowaniu x2...\n";
    std::cout << "Pole wynosi teraz: " << rect.area() << "\n";

    Rectangle kwadrat = Rectangle::createSquare(10.0);
    std::cout << "\nPole utworzonego kwadratu: " << kwadrat.area() << "\n";
    std::cout << "Czy kwadrat? " << (kwadrat.isSquare() ? "Tak" : "Nie") << "\n";

    return 0;
}
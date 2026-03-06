#include "Car.hpp"
#include <iostream>

int main()
{
    Car myCar("Toyota", 180.0);

    myCar.printInfo();

    std::cout << "\nPrzyspieszamy o 50 km/h...\n";
    myCar.accelerate(50.0);
    myCar.printInfo();

    std::cout << "\nHamujemy o 20 km/h...\n";
    myCar.brake(20.0);
    myCar.printInfo();

    return 0;
}
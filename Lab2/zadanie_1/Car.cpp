#include "Car.hpp"
#include <iostream>

Car::Car(std::string brand, double maxSpeed) 
    : brand(brand), speed(0.0), maxSpeed(maxSpeed) {
}

void Car::accelerate(double amount) {
    if (amount > 0.0) {
        speed += amount;
        if (speed > maxSpeed) {
            speed = maxSpeed;
        }
    }
}

void Car::brake(double amount) {
    if (amount > 0.0) {
        speed -= amount;
        if (speed < 0.0) {
            speed = 0.0;
        }
    }
}

double Car::getSpeed() const {
    return speed;
}

void Car::printInfo() const {
    std::cout << "Marka: " << brand 
              << ", Aktualna predkosc: " << speed 
              << " / " << maxSpeed << " km/h" << std::endl;
}
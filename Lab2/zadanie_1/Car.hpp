#ifndef CAR_HPP
#define CAR_HPP

#include <string>

class Car
{
private:
    std::string brand;
    double speed;
    double maxSpeed;

public:
    Car(std::string brand, double maxSpeed);
    void accelerate(double amount);
    void brake(double amount);
    double getSpeed() const;
    void printInfo() const;
};

#endif // CAR_HPP
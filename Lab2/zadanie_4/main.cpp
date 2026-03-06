#include "Player.hpp"
#include <iostream>

int main() {
    Player p1("Geralt", 100);
    p1.printStatus();

    std::cout << "\nOtrzymuje 30 obrazen...\n";
    p1.takeDamage(30);
    p1.printStatus();

    std::cout << "\nLeczy sie o 50 (nie moze przekroczyc maksa!)...\n";
    p1.heal(50);
    p1.printStatus();

    std::cout << "\nOtrzymuje potężny cios za 200 obrazen...\n";
    p1.takeDamage(200);
    p1.printStatus();

    p1.levelUp();
    p1.printStatus();

    return 0;
}
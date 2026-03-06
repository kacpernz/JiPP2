#include "Player.hpp"
#include <iostream>

Player::Player(std::string name, int maxHp) 
    : name(name), hp(maxHp), maxHp(maxHp), level(1) {
}

void Player::takeDamage(int damage) {
    if (damage > 0) {
        hp -= damage;
        if (hp < 0) {
            hp = 0;
        }
    }
}

void Player::heal(int amount) {
    if (amount > 0) {
        hp += amount;
        if (hp > maxHp) {
            hp = maxHp;
        }
    }
}

void Player::levelUp() {
    level++;
    maxHp += 10; 
    hp = maxHp;  
    std::cout << "\n*** " << name << " awansuje na poziom " << level << "! ***\n";
}

void Player::printStatus() const {
    std::cout << "Gracz: " << name 
              << " | Poziom: " << level 
              << " | HP: " << hp << "/" << maxHp << "\n";
}
#ifndef Player_HPP
#define Player_HPP

#include <string>

class Player {
    private:
        std::string name;
        int hp;
        int maxHp;
        int level;

    public:
        Player(std::string name, int maxHp);
        void takeDamage(int damage);
        void heal(int amount);
        void levelUp();
        void printStatus() const;
};

#endif // Player_HPP
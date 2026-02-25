#pragma once
#include <string>
#include <algorithm>

class Renderable {
public:
    int x, y; //position
    char symbol;
    virtual ~Renderable() = default;
    //int color = 37; //for later use when colors implemented
};

class Monster : public Renderable {
private: 
    int health, damage;
    std::string name;
public:
    Monster(std::string Monstername, int startX, int startY, int hp, int dmg, char sym)
        : name(Monstername), x(startX), y(startY), health(hp), damage(dmg), symbol(sym) {}
    
    void takeDamage(int damage) { 
        health = std::max(0, health - damage); 
    }
    int getHealth() const {return health; }
    int getDamage() const {return damage; }
    std::string getName() const {return name; }

    bool isAlive() const { return health > 0; }
};
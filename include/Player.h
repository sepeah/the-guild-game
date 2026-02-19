//Player class header file

#pragma once
#include <string>
#include <vector>
#include <algorithm>

class Player {
private:
    int x, y;       //position
    int health, maxHealth, lvl;
    std::string name;

    int purse;
    int lockpicking;
    std::vector<std::string> inventory; //simple inventory for now

public:
    // Constructor
    Player(std::string playerName, int startX, int startY)
        : name(playerName), x(startX), y(startY), health(10), maxHealth(10), lvl(1),
          purse(10), lockpicking(0), inventory({"Small knife"}){}
    
    // Getters and setters
    int getX() const { return x; }
    int getY() const { return y; }
    void setPosition(int newX, int newY) { x = newX; y = newY; }
    
    // Damage system
    void takeDamage(int damage) {
        health = std::max(0, health - damage);
    }
    
    void heal(int amount) {
        health = std::min(maxHealth, health + amount);
    }
    
    bool isAlive() const { return health > 0; }
    };
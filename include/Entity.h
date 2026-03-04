#pragma once
#include <string>
#include <algorithm>

class Game; //Forward declaration for interaction methods

class Renderable {
public:
    int x, y; //position
    char symbol;
    
    Renderable(int posX, int posY, char sym) : x(posX), y(posY), symbol(sym) {}
    virtual ~Renderable() = default;
    //int color = 37; //for later use when colors implemented
};

class Monster : public Renderable {
private: 
    int health, damage;
    std::string name;
public:
    Monster(std::string Monstername, int startX, int startY, int hp, int dmg, char sym)
        : Renderable(startX, startY, sym), name(Monstername), health(hp), damage(dmg) {}
    
    void takeDamage(int damage) { 
        health = std::max(0, health - damage); 
    }
    int getHealth() const {return health; }
    int getDamage() const {return damage; }
    std::string getName() const {return name; }

    bool isAlive() const { return health > 0; }
};

class MapObject : public Renderable {
protected:
    std::string name;
public:
    MapObject(std::string Objectname, int startX, int startY, char sym)
        : Renderable(startX, startY, sym), name(Objectname) {}

    virtual void interact(Game* game) = 0; // Pure virtual for interaction
    virtual bool blocksMovement() const = 0;
    std::string getName() const { return name; }
};

class Door : public MapObject {
private:
    bool isOpen;
    bool isLocked;
public:
    Door(int x, int y, bool locked = false) 
        : MapObject("a door", x, y, '+'), isOpen(false), isLocked(locked) {}
    
    void interact(Game* game) override;  // implementation in Entity.cpp
    bool blocksMovement() const override { return !isOpen; }
};

class Counter : public MapObject {
public:
    Counter(int x, int y) 
        : MapObject("the bar counter", x, y, '=') {}
    
    void interact(Game* game) override;  // implementation in Entity.cpp
    bool blocksMovement() const override { return true; }
};
#pragma once
#include <string>
#include <algorithm>
#include "ItemDatabase.h"

class Game; //Forward declaration for interaction methods

class Renderable {
public:
    int x, y; //position
    char symbol;
    
    Renderable(int posX, int posY, char sym) : x(posX), y(posY), symbol(sym) {}
    virtual ~Renderable() = default;
    //int color = 37; //for later use when (or if) colors implemented
};

class LivingEntity : public Renderable {
private: 
    int health, damage;
    std::string name;
public:
    LivingEntity(std::string entityName, int startX, int startY, int hp, int dmg, char sym)
        : Renderable(startX, startY, sym), name(entityName), health(hp), damage(dmg) {}
    
    virtual void interact(Game* game) = 0;
    virtual bool isHostile() const = 0;
    virtual bool blocksMovement() const {return true;};

    virtual void takeTurn(Game* game) {// Default: do nothing - override for entities with AI
    };

    void takeDamage(int damage) { 
        health = std::max(0, health - damage); 
    }
    int getHealth() const {return health; }
    int getDamage() const {return damage; }
    std::string getName() const {return name; }

    bool isAlive() const { return health > 0; }
};

class Monster : public LivingEntity {
public:
    Monster(std::string monsterName, int startX, int startY, int hp, int dmg, char sym)
        : LivingEntity(monsterName, startX, startY, hp, dmg, sym) {}

    void interact(Game* game) override; // Combat interaction    
    void takeTurn(Game* game) override; // AI behavior    
    bool isHostile() const override { return true; }
};

class NPC : public LivingEntity {
public:
    NPC(std::string NPCName, int startX, int startY, int hp, int dmg, char sym)
        : LivingEntity(NPCName, startX, startY, hp, dmg, sym) {}

    void interact(Game* game) override; // Conversation interaction    
    //void takeTurn(Game* game) override; // AI behavior - NPCs might just stand still    
    bool isHostile() const override { return false; }
};

class MapObject : public Renderable {
protected:
    std::string name;
public:
    MapObject(std::string Objectname, int startX, int startY, char sym)
        : Renderable(startX, startY, sym), name(Objectname) {}

    virtual void interact(Game* game) = 0; // Pure virtual for interaction
    virtual void onEnterTile(Game* game) {}; // Optional override for when player steps on tile
    virtual bool blocksMovement() const = 0;
    virtual bool shouldRemove() const { return false; }
    std::string getName() const { return name; }
};

class GroundItem : public MapObject {
private:
    std::string itemId;
    int quantity;
    bool pickedUp;
public:
    GroundItem(const std::string& id, int x, int y, int amount = 1)
        : MapObject(id, x, y, ItemDatabase::getStats(id).mapSymbol),
          itemId(id), quantity(std::max(1, amount)), pickedUp(false) {}

    void interact(Game* game) override;
    void onEnterTile(Game* game) override;
    bool blocksMovement() const override { return false; }
    bool shouldRemove() const override { return pickedUp; }
};

class Corpse : public MapObject {
private:
    std::string sourceMonsterId;
    std::string sourceMonsterName;

public:
    Corpse(const std::string& monsterId, const std::string& monsterName, int x, int y)
        : MapObject("corpse", x, y, '%'),
          sourceMonsterId(monsterId),
          sourceMonsterName(monsterName) {}

    void interact(Game* game) override;
    void onEnterTile(Game* game) override;
    bool blocksMovement() const override { return false; }

    const std::string& getSourceMonsterId() const { return sourceMonsterId; }
    const std::string& getSourceMonsterName() const { return sourceMonsterName; }
}; 

class Door : public MapObject {
private:
    bool isOpen;
    bool isLocked;
public:
    Door(int x, int y, bool locked = false) 
        : MapObject("a door", x, y, '+'), isOpen(false), isLocked(locked) {}
    
    void interact(Game* game) override;  // implementation in Entity.cpp
    void onEnterTile(Game* game) override;
    bool blocksMovement() const override { return !isOpen; }
};

class Counter : public MapObject {
public:
    Counter(int x, int y) 
        : MapObject("the bar counter", x, y, '=') {}
    
    void interact(Game* game) override;  // implementation in Entity.cpp
    bool blocksMovement() const override { return true; }
};
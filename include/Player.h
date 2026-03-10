//Player class

#pragma once
#include <string>
#include <algorithm>
#include <unordered_map>

class Player {
private:
    int x, y;       //position
    int health, maxHealth, lvl;
    std::string name;

    int purse;
    int lockpicking;
    int damagebonus;
    std::unordered_map<std::string, int> inventory;

public:
    // Constructor
    Player(std::string playerName, int startX, int startY)
        : name(playerName), x(startX), y(startY), health(10), maxHealth(10), lvl(1),
          purse(10), damagebonus(0), lockpicking(0), inventory({{"Small knife", 1}}) {}
    
    // Getters and setters
    int getX() const { return x; }
    int getY() const { return y; }
    void setPosition(int newX, int newY) { x = newX; y = newY; }
    int getHealth() const {return health; }
    int getMaxHealth() const {return maxHealth; }
    int getDamage() const { return 2; } // Base damage for now, can be modified by weapons later
    const std::string& getName() const { return name; }

    // Money system
    int getPurse() const { return purse; }
    void addCoins(int amount) { purse += amount; }
    bool spendCoins(int amount) { 
        if (purse >= amount) {
            purse -= amount;
            return true;  // Transaction successful
        }
        return false;  // Not enough money
    }
    
    // Inventory system
    void addItem(const std::string& itemId, int quantity = 1) {
        if (quantity <= 0) return;
        inventory[itemId] += quantity;
    }

    bool hasItem(const std::string& itemId) const {
    auto it = inventory.find(itemId);
    return it != inventory.end();
    }
    
    int getItemCount(const std::string& itemId) const {
    auto it = inventory.find(itemId);
    return (it != inventory.end()) ? it->second : 0;
    }

    bool removeItem(const std::string& itemId, int quantity = 1) {
        if (quantity <= 0) return false;
        
        int current = getItemCount(itemId);
        if (current < quantity) return false;
        
        if (current == quantity) {
            inventory.erase(itemId); // remove key when count hits 0
        } else {
            inventory[itemId] -= quantity;
        }
        return true;
    }

    const std::unordered_map<std::string, int>& getInventory() const {
    return inventory;
    }
    
    // Damage system
    void takeDamage(int damage) {
        health = std::max(0, health - damage);
    }
    
    void heal(int amount) {
        health = std::min(maxHealth, health + amount);
    }
    
    bool isAlive() const { return health > 0; }
    };
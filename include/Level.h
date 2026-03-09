#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "Entity.h"
#include "MonsterDatabase.h"

/**
 * Base class for all game levels/areas
 * Handles map data and provides room descriptions
 */


class Level {
public:
    std::vector<std::string> map;
    std::string name;
    std::vector<std::unique_ptr<MapObject>> objects;
    std::vector<std::unique_ptr<LivingEntity>> livingEntities;
    Level(std::vector<std::string> levelMap, std::string levelName)
        : map(levelMap), name(levelName) {}
    virtual ~Level() = default;

    virtual std::string getRoomDescription(int x, int y) const {
        return "You are in " + name + " at position (" + std::to_string(x) + "," + std::to_string(y) + ")";
    }
};


/**
 * Initial Tavern level with descriptions overriding the base class
 */

class TavernLevel : public Level {
public:
    TavernLevel() : Level({
        "###########################",
        "..........................#",
        "#..................#......#",
        "#..................#......#",
        "#..................#......#",
        "###########################"
    }, "A dimly lit tavern") {
    MonsterDatabase::initialize();
    
    // Add rats using MonsterDatabase
    auto ratStats = MonsterDatabase::getStats("rat");
    livingEntities.push_back(std::make_unique<Monster>("rat", 5, 2, ratStats.health, ratStats.damage, ratStats.symbol));
    livingEntities.push_back(std::make_unique<Monster>("rat", 15, 3, ratStats.health, ratStats.damage, ratStats.symbol));
    livingEntities.push_back(std::make_unique<Monster>("black rat", 22, 3, ratStats.health, ratStats.damage, ratStats.symbol));
    livingEntities.push_back(std::make_unique<Monster>("rat", 3, 2, ratStats.health, ratStats.damage, ratStats.symbol));
    livingEntities.push_back(std::make_unique<Monster>("rat", 6, 2, ratStats.health, ratStats.damage, ratStats.symbol));
    
    
    objects.push_back(std::make_unique<Door>(19, 1, false)); // Unlocked door
    objects.push_back(std::make_unique<Counter>(10, 3));
    objects.push_back(std::make_unique<Counter>(11, 3));
    objects.push_back(std::make_unique<Counter>(12, 3));
    objects.push_back(std::make_unique<Counter>(13, 3));
    }
    
    std::string getRoomDescription(int x, int y) const override {
        
        if (x < 14 && x > 9 && y < 3 && y > 1) {
            return "The counter has a massive barrel on top. \"Two coins for a mug of ale!\", barks the grumpy barkeep.";
        }
        else if (x < 19 && x > 0) {
            return "A cosy tavern, but you get strange looks, the patrons seem unfriendly.";
        }
        else if (x > 18) {
            return "This seems to be a private area. A scar-faced old man glares at you from the corner.";
        }
        else if(x < 1) {
            return "It's still raining, you REALLY don't want to go out.";
        }
        else {
            return "You find yourself in an unremarkable part of the tavern, with worn wooden floors and flickering candlelight.";
        }
    }
};

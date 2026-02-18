//Item Database header file

#pragma once
#include <string>
#include <map>
#include <vector>

/**
 * Structure for item properties
 */
struct ItemStats {
    int damage = 0;           // Weapon damage (1d4, etc.)
    int armorBonus = 0;       // Protection from damage
    bool magic = false;      // magic items have special effects
    int value = 0;            // Gold value for buying/selling
    std::string description;  // Flavor text
    // skill bonuses
    std::map<std::string, int> skillBonuses;
    char mapSymbol = '?';
};

/**
 * Static database of all game items
 * Provides stats lookup for string-based inventory system
 */
class ItemDatabase {
private:
    static std::map<std::string, ItemStats> items;
    static bool initialized;

public:
    // Initialize the item database with all game items
    static void initialize();
    
    // Get item stats by name
    static ItemStats getStats(const std::string& itemName);
    
    // Check if item exists in database
    static bool exists(const std::string& itemName);
    
    // Get all item names (for testing/debugging)
    static std::vector<std::string> getAllItemNames();
};
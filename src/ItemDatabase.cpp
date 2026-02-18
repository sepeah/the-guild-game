//Item Database implementation

#include "ItemDatabase.h"
#include <vector>

std::map<std::string, ItemStats> ItemDatabase::items;
bool ItemDatabase::initialized = false;

void ItemDatabase::initialize() {
    if (initialized) return;  // Only initialize once
    
    //            WEAPONS

    items["Small knife"] = {
        .damage = 2,           // 1d4 average damage  
        .armorBonus = 0,
        .magic = false,
        .value = 5,
        .description = "A worn but sharp blade, always useful to have",
        .skillBonuses = {},
        .mapSymbol = '/'
    };
    
    items["Thieves' Dagger"] = {
        .damage = 3,
        .armorBonus = 0,
        .magic = false,
        .value = 25,
        .description = "A Long, slender and deadly steel blade.",
        .skillBonuses = {},
        .mapSymbol = '/'
    };
    
    
    //             TOOLS

    items["Lockpicks"] = {
        .damage = 0,
        .armorBonus = 0,
        .magic = false,
        .value = 5,
        .description = "A set of bent metal wires. Essential for any... locksmith.",
        .skillBonuses = {{"lockpicking", 10}},
        .mapSymbol = '='
    };
    
    items["Masterwork Lockpicks"] = {
        .damage = 0,
        .armorBonus = 0,
        .magic = false,
        .value = 75,
        .description = "Skillfully crafted tools of \"the trade\".",
        .skillBonuses = {{"lockpicking", 20}},
        .mapSymbol = '='
    };
    
    //         ARMOR/CLOTHING

    items["Worn Cloak"] = {
        .damage = 0,
        .armorBonus = 1,       // Light protection
        .magic = false,
        .value = 10,
        .description = "A dark cloak to shield against the elements.",
        .skillBonuses = {},
        .mapSymbol = '"'
    };
    
    items["Leather Armor"] = {
        .damage = 0,
        .armorBonus = 3,
        .magic = false,
        .value = 50,
        .description = "A Sturdy leather vest.",
        .skillBonuses = {},
        .mapSymbol = '['
    };
    
    //          MISC ITEMS

    items["Bread"] = {
        .damage = 0,
        .armorBonus = 0,
        .magic = false,
        .value = 1,
        .description = "A simple dark loaf.",
        .skillBonuses = {},
        .mapSymbol = '%'
    };
    
    items["Rings of The Two Hands"] = {
        .damage = 0,
        .armorBonus = 0,
        .magic = false,
        .value = 0,
        .description = "Two simple rings, one iron, one silver.",
        .skillBonuses = {},
        .mapSymbol = '*'
    };
    
    initialized = true;
}

ItemStats ItemDatabase::getStats(const std::string& itemName) {
    initialize();  // Auto-initialize if not done
    
    auto it = items.find(itemName);
    if (it != items.end()) {
        return it->second;
    }
    
    // Return default stats for unknown items
    return ItemStats{0, 0, false, 0, "Unknown item", {}, '?'};
}

bool ItemDatabase::exists(const std::string& itemName) {
    initialize();
    return items.find(itemName) != items.end();
}

std::vector<std::string> ItemDatabase::getAllItemNames() {
    initialize();
    
    std::vector<std::string> names;
    for (const auto& pair : items) {
        names.push_back(pair.first);
    }
    return names;
}
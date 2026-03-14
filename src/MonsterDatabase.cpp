#include "MonsterDatabase.h"

std::map<std::string, MonsterStats> MonsterDatabase::monsters;
bool MonsterDatabase::initialized = false;

void MonsterDatabase::initialize() {
    if (initialized) return;
    
    monsters["rat"] = {
        .health = 4,
        .damage = 2,
        .symbol = 'r',
        .description = "A dirty rat",
        .leavesCorpse = true,
        .requiresMagic = false
    };
    
    monsters["ghost of the cursed rat"] = {
        .health = 4,
        .damage = 3,
        .symbol = 'g',
        .description = "A dirty ghost",
        .leavesCorpse = false,
        .requiresMagic = true
    };
    
    // Future monsters here
    
    initialized = true;
}

MonsterStats MonsterDatabase::getStats(const std::string& monsterName) {
    initialize();  // Auto-initialize if not done
    
    auto it = monsters.find(monsterName);
    if (it != monsters.end()) {
        return it->second;
    }
    
    // Return default stats for unknown items
    return MonsterStats{0, 0, '?', "Unknown creature", false};
}

bool MonsterDatabase::exists(const std::string& monsterName) {
    initialize();
    return monsters.find(monsterName) != monsters.end();
}

std::vector<std::string> MonsterDatabase::getAllMonsterNames() {
    initialize();
    
    std::vector<std::string> names;
    for (const auto& pair : monsters) {
        names.push_back(pair.first);
    }
    return names;
}
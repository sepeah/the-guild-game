#pragma once
#include <string>
#include <map>
#include <vector>

struct MonsterStats {
    int health;
    int damage;
    char symbol;
    std::string description;
    bool leavesCorpse;
    bool requiresMagic;
};

class MonsterDatabase {
private:
    static std::map<std::string, MonsterStats> monsters;
    static bool initialized;

public:
    static void initialize();
    static MonsterStats getStats(const std::string& monsterName);
    static bool exists(const std::string& monsterName);
    static std::vector<std::string> getAllMonsterNames();
};


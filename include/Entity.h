#pragma once
#include <string>

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
    std:string Monstername;
public:
    Monster(std::string Monstername)
        : name(Monstername), name(levelName) {}



}
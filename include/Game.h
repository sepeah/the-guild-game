#pragma once
#include <memory>
#include <string>
#include <iostream>
#include <conio.h>        // For _getch() - known platform dependency

#include "Player.h"
#include "Level.h"
#include "ItemDatabase.h"

class Game {
private:
    // Game state
    std::unique_ptr<Level> currentLevel;
    Player player;
    bool gameRunning;
    
    // Core game loop methods
    void render();
    void handleInput(); 
    void update();
    
    // Input abstraction (for future platform portability)
    char getPlayerInput() { return _getch(); }
    
    // Rendering components
    void renderMap();
    void renderStatusPanel();
    std::string buildScreen();
    
public:
    Game();
    ~Game() = default;
    
    // Main interface
    void run();
};
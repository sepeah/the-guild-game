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
    
    // Clear screen
    void clearScreen();
    
    // Collision detection
    bool canMoveToPosition(int x, int y);

    // Rendering components
    void renderMap();
    void renderStatusPanel();
    std::string buildScreen();
    std::string statusMessage;
    
public:
    Game();
    ~Game() = default;
    void setMessage(const std::string& msg) { statusMessage = msg; }
    void appendMessage(const std::string& msg) { statusMessage += msg; }   
    void clearMessage() { statusMessage = ""; }
    Player& getPlayer() { return player; } 
    bool canEntityMoveToPosition(int x, int y);
    // Main interface
    void run();
    void openInventory();
};
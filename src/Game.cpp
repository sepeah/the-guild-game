#include "Game.h"
#include "Level.h"

// Constructor - Initialize all game systems
Game::Game() : player("Clueless Adventurer", 2, 2), gameRunning(true) {
    ItemDatabase::initialize();
    currentLevel = std::make_unique<TavernLevel>();
}

// Main game loop
void Game::run() {
    while (gameRunning) {
        render();
        handleInput();
        // update(); // Added in future iterations for more complex game logic
    }
}

void Game::render() {
    // Get player position from Player class
    int px = player.getX();
    int py = player.getY();
    
    // Build entire screen in memory to reduce flickering
    std::string screen = "\033[2J\033[H";  // Clear screen and move to top
    
    // Build map + player using Level class
    for (int y = 0; y < currentLevel->map.size(); y++) {
        for (int x = 0; x < currentLevel->map[y].size(); x++) {
            if (x == px && y == py)
                screen += '@';
            else
                screen += currentLevel->map[y][x];  // Access Level's map through smart pointer
        }
        screen += "\n";
    }
    
    // Build status panel using class methods  
    screen += "\n" + std::string(40, '=') + "\n";
    screen += currentLevel->getRoomDescription(px, py) + "\n";  // Polymorphic method call
    screen += "POSITION: (" + std::to_string(px) + ", " + std::to_string(py) + ")\n";
    screen += "HEALTH: 100/100\n";  // TODO: Use player health later
    screen += std::string(40, '=') + "\n";
    screen += "Commands: WASD=Move, Q=Quit\n";
    
    // Output everything at once
    std::cout << screen << std::flush;
}

void Game::handleInput() {
    char c = getPlayerInput();

    // Get current player position from Player class
    int currentX = player.getX(); 
    int currentY = player.getY();

    int newX = currentX, newY = currentY;
    if (c == 'w') newY--;
    if (c == 's') newY++;
    if (c == 'a') newX--;
    if (c == 'd') newX++;
    
    // Collision detection. Player moves only to floor "."
    if (currentLevel->map[newY][newX] == '.') {
        player.setPosition(newX, newY);
    }

    // Quit command
    if (c == 'q') gameRunning = false;  // Set flag to exit game loop
}

// stub implementations for next phase of development
void Game::renderMap() { 
    // TODO: Extract map rendering from render() method later
}

void Game::renderStatusPanel() { 
    // TODO: Extract status panel from render() method later 
}

std::string Game::buildScreen() { 
    // TODO: Extract screen building from render() method later
    return ""; 
}

void Game::update() { 
    // TODO: Add game state updates later
}
#include "Game.h"
#include "Level.h"

// Constructor - Initialize all game systems
Game::Game() : player("Clueless Adventurer", 1, 1), gameRunning(true) {
    ItemDatabase::initialize();
    MonsterDatabase::initialize();
    currentLevel = std::make_unique<TavernLevel>();
}

// Main game loop
void Game::run() {
    while (gameRunning && player.isAlive()) {
        render();
        handleInput();
        update();
    }
    
    if (!player.isAlive()) {
        clearScreen();
        std::cout << "\n\n\n    Death, the inevitable.\n     With a gentle hand She caresses you, and just like that...\n      She stills the beating of your heart,\n       and your consciousness... \n\n\n";
    }
}

void Game::clearScreen() {
    std::cout << "\033[2J\033[H" << std::flush;
}

void Game::render() {
    // Get player position from Player class
    int px = player.getX();
    int py = player.getY();
    
    // Build entire screen in memory to reduce flickering
    std::string screen;

    // Build character info panel using class methods  
    screen += "\n" + player.getName() +"     Health: " + std::to_string(player.getHealth()) + "/" + std::to_string(player.getMaxHealth()) + "     Coins: " + std::to_string(player.getPurse()) +"\n\n";
    
    // Build map + player + renderables using Level class
    for (int y = 0; y < currentLevel->map.size(); y++) {
        for (int x = 0; x < currentLevel->map[y].size(); x++) {
            char renderChar = currentLevel->map[y][x];  // Start with map
            
            // Check for objects at this position
            for (const auto& obj : currentLevel->objects) {
                if (obj->x == x && obj->y == y) {
                    renderChar = obj->symbol;
                    break;  // Objects have priority over map
                }
            }
            // Check for living entitities at this position
            for (const auto& entity : currentLevel->livingEntities) {
                if (entity->x == x && entity->y == y) {
                    renderChar = entity->symbol;
                    break;  // Entities have priority over map
                }
            }
            
            // Check for player (highest priority)
            if (x == px && y == py) {
                renderChar = '@';
            }
            
            screen += renderChar;
        }
        screen += "\n";
    }
    
    // Build status panel using class methods  
    screen += "\n" + std::string(80, '=') + "\n";
    screen += currentLevel->getRoomDescription(px, py) + "\n";  // Polymorphic method call
    screen += statusMessage + "\n";  // Display any status messages
    screen += "POSITION: (" + std::to_string(px) + ", " + std::to_string(py) + ")\n";
    screen += std::string(80, '=') + "\n";
    screen += "Commands: WASD=Move, Q=Quit\n";
    
    // Clear screen and display everything at once
    clearScreen();
    std::cout << screen << std::flush;
}

void Game::handleInput() {
    clearMessage();
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
    if (canMoveToPosition(newX, newY)) {
        player.setPosition(newX, newY);
    } else {
        // Check for interactive object
        for (const auto& obj : currentLevel->objects) {
            if (obj->x == newX && obj->y == newY) {
                obj->interact(this);  // Try to interact
                break;
            }
        }
        // Check for interactive entity
        for (const auto& entity : currentLevel->livingEntities) {
            if (entity->x == newX && entity->y == newY) {
                entity->interact(this);  // Try to interact
                break;
            }
        }
    }

    // Quit command
    if (c == 'q') gameRunning = false;  // Set flag to exit game loop
}

bool Game::canEntityMoveToPosition(int x, int y) {
    // Check map boundaries
    if (y < 0 || x < 0 ||
    y >= static_cast<int>(currentLevel->map.size()) ||
    x >= static_cast<int>(currentLevel->map[y].size())) {
    return false;
    }
    // Check base map tile
    if (currentLevel->map[y][x] != '.') 
        return false;  // Wall, etc.
    
        // Check for player
    if (player.getX() == x && player.getY() == y) {
        return false;
    }
    // Check for blocking objects
    for (const auto& obj : currentLevel->objects) {
        if (obj->x == x && obj->y == y && obj->blocksMovement()) {
            return false;
        }
    }
    // Check for blocking entities
    for (const auto& entity : currentLevel->livingEntities) {
        if (entity->x == x && entity->y == y && entity->blocksMovement()) {
            return false;
        }
    }
   
    return true;  // Position is clear
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
    for (const auto& entity : currentLevel->livingEntities) {
        entity->takeTurn(this);
    }
}

bool Game::canMoveToPosition(int x, int y) {
    // Check map boundaries
    if (y < 0 || x < 0 ||
    y >= static_cast<int>(currentLevel->map.size()) ||
    x >= static_cast<int>(currentLevel->map[y].size())) {
    return false;
    }
    // Check base map tile
    if (currentLevel->map[y][x] != '.') 
        return false;  // Wall, etc.
    
    // Check for blocking objects
    for (const auto& obj : currentLevel->objects) {
        if (obj->x == x && obj->y == y && obj->blocksMovement()) {
            return false;
        }
    }
    // Check for blocking entities
    for (const auto& entity : currentLevel->livingEntities) {
        if (entity->x == x && entity->y == y && entity->blocksMovement()) {
            return false;
        }
    }
   
    return true;  // Position is clear
}
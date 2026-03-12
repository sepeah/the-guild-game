#include "Entity.h"
#include "Game.h"  // Now we can include the full Game definition
#include <cmath>
#include <cstdlib>

void GroundItem::onEnterTile(Game* game) {
    std::string message = "";
    if (quantity > 1) {
        message += std::to_string(quantity) + "x ";
    }
    message += itemId + ". ";
    game->appendMessage(message);
}

void GroundItem::interact(Game* game) {
    if (pickedUp) {
        return;
    }

    Player& player = game->getPlayer();
    player.addItem(itemId, quantity);

    std::string message = "You pick up ";
    if (quantity == 1) {
        message += "the ";
    }
    if (quantity > 1) {
        message += std::to_string(quantity) + "x ";
    }
    message += itemId + ". ";

    game->appendMessage(message);
    pickedUp = true;
}

void Door::interact(Game* game) {
    if (isLocked) {
        game->appendMessage("The door is locked. ");
    } else if (!isOpen) {
        isOpen = true;
        symbol = '/';
        game->appendMessage("You open the door. ");
    } else {
        game->appendMessage("Something is wrong with this door. ");
    }
}
void Door::onEnterTile(Game* game) {
    if (isOpen) {
        game->appendMessage("An open door. Press C to close. ");
    }
    else {
        game->appendMessage("A closed door");

    }    
}


void Counter::interact(Game* game) {
    Player& player = game->getPlayer();
    if (player.spendCoins(2)) {
        game->appendMessage("The barkeep grabs your coins and hands you a mug of ale. ");
        player.addItem("Mug of Ale", 1);
    } 
    else {
        game->appendMessage("\"Get out of here, you dog! Come back when you have some coins! \"");
    }
}

void Monster::takeTurn(Game* game) {
    // Simple AI
    if (!isAlive()) return; // Dead monsters do nothing
    
    
    
    if (isHostile()) {    // aggressive monsters attack player if adjacent
        Player& player = game->getPlayer();
        int dx = std::abs(player.getX() - x);
        int dy = std::abs(player.getY() - y);
        
        if ((dx == 1 && dy == 0) || (dx == 0 && dy == 1)) {
            game->appendMessage("The " + getName() + " attacks! ");
            interact(game); // Attack player if adjacent
            return; // Attack instead of moving
        }
    }
    std::pair<int,int> dirs[4] = {
    {1, 0},
    {0, 1},
    {0, -1},
    {-1, 0}
    };
    std::pair<int,int> dir = dirs[std::rand() % 4];
    int newX = x + dir.first;
    int newY = y + dir.second;

    if (!game->canEntityMoveToPosition(newX, newY)) {
        return; // Can't move, so skip turn
    }
    x = newX;
    y = newY;


}

void Monster::interact(Game* game) {
    if (!isAlive()) {
        game->appendMessage("The " + getName() + " lies dead.");
        return;
    }
    Player& player = game->getPlayer();
    takeDamage(player.getDamage());
    game->appendMessage("You hit the " + getName() + " for " + std::to_string(player.getDamage()) + " damage! ");
    if (!isAlive()) {
        game->appendMessage("The " + getName() + " dies! ");
        return;
    }
    if (isAlive()) {
        player.takeDamage(getDamage());
        game->appendMessage("The " + getName() + " attacks you for " + std::to_string(getDamage()) + " damage! ");
    }
}

void NPC::interact(Game* game) {
    game->appendMessage("The " + getName() + " looks at you expectantly. ");
}


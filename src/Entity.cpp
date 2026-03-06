#include "Entity.h"
#include "Game.h"  // Now we can include the full Game definition

void Door::interact(Game* game) {
    if (isLocked) {
        game->appendMessage("The door is locked. ");
    } else if (!isOpen) {
        isOpen = true;
        symbol = '/';
        game->appendMessage("You open the door. ");
    } else {
        game->appendMessage("The door is already open. ");
    }
}


void Counter::interact(Game* game) {
    Player& player = game->getPlayer();
    if (player.spendCoins(2)) {
        game->appendMessage("The barkeep grabs your coins and hands you a mug of ale. ");
    } 
    else {
        game->appendMessage("\"Get out of here, you dog! Come back when you have some coins! \"");
    }
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


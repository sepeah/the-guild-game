#include "Entity.h"
#include "Game.h"  // Now we can include the full Game definition

void Door::interact(Game* game) {
    if (isLocked) {
        game->setMessage("The door is locked.");
    } else if (!isOpen) {
        isOpen = true;
        symbol = '/';
        game->setMessage("You open the door.");
    } else {
        game->setMessage("The door is already open.");
    }
}

void Counter::interact(Game* game) {
    Player& player = game->getPlayer();
    if (player.spendCoins(2)) {
        game->setMessage("The barkeep grabs your coins and hands you a mug of ale. ");
    } 
    else {
        game->setMessage("\"Get out of here, you dog! Come back when you have some coins!\"");
    }
}
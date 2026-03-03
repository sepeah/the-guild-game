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
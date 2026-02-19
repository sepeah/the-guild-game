#include "Game.h"
#include <conio.h>

int main() {
    std::cout << "\033[2J\033[H";
    std::cout << "\n\n";
    std::cout << "\"This is the Guild, the Two Hands and the Ten Hands, \n"
              << " the Five, the Ten, the Fifty Fingers!\n"
              << " I am the second Thumb of the Left Hand.\n" 
              << " What the Hands have, will not leave of its own accord.\"\n" << std::endl;
    std::cout << " It's raining. Press any key to enter the tavern...\n\n";
    _getch();  // Waits for any key press
    
    Game game;
    game.run();
    return 0;
}
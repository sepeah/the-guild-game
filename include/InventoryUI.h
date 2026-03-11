#pragma once
#include <string>
#include <vector>
#include "ItemDatabase.h"
#include "Player.h"

class InventoryUI {
private:
    Player& player;

    // Snapshot of inventory item IDs shown in the current screen order.
    std::vector<std::string> orderedItems;
    // Cursor position in orderedItems.
    int selectedIndex = 0;
    // Message returned to Game status panel when inventory closes.
    std::string pendingMessage;

    // Rebuild orderedItems from the player's current inventory contents.
    void rebuildItemList();
    // Draw the inventory window, selected item details, and controls.
    void render() const;

    // Read one keypress for inventory-local controls.
    char readKey() const;
    // True when the key is ESC (close inventory).
    bool isEscapeKey(char key) const;

    // True if selectedIndex points to a valid item.
    bool hasSelection() const;
    // Get currently selected item ID or empty string if selection is invalid.
    std::string getSelectedItemId() const;
    // Get description text for currently selected item from ItemDatabase.
    std::string getSelectedItemDescription() const;
    // Move selection cursor up by one (with bounds handling).
    void moveSelectionUp();
    // Move selection cursor down by one (with bounds handling).
    void moveSelectionDown();

    // Handle action keys (u/d/w and optional navigation); returns true if handled.
    bool handleActionKey(char key);
    // Use the selected item (eat, drink, read, etc.) if applicable.
    void useSelectedItem();
    // Drop one instance of the selected item.
    void dropSelectedItem();
    // Wield/wear selected item based on its stats (damage/armor).
    void wieldWearSelectedItem();

public:
    InventoryUI(Player& p) : player(p) {}
    // Open modal inventory loop and return final action message for the game UI.
    std::string run();
};

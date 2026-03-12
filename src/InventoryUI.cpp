#include "InventoryUI.h"

#include <algorithm>
#include <conio.h>
#include <iostream>

void InventoryUI::rebuildItemList() {
    orderedItems.clear();
    for (const auto& pair : player.getInventory()) {
        orderedItems.push_back(pair.first);
    }
    std::sort(orderedItems.begin(), orderedItems.end());
    if (orderedItems.empty()) {
        selectedIndex = 0;
    } else {
        selectedIndex = std::min(selectedIndex, static_cast<int>(orderedItems.size()) - 1);
    }
}

void InventoryUI::render() const {

    // Build inventory screen in memory first
    std::string inventoryScreen;
	std::string quantityprompt;
  
    inventoryScreen += 
    "\n  " + player.getName() +"     Inventory.    \n\n" 
    + "COMMANDS: J/K=move selection, U=use, D=drop, W=wield/wear, ESC=exit " +"\n\n"
    +"Coins: " + std::to_string(player.getPurse()) +"\n\n" 
    + "  Items:                Quantity:"+"\n\n";
    
    // items with quantity and > for selected item
    for (std::size_t i = 0; i < orderedItems.size(); ++i) {
        const std::string& element = orderedItems[i];

        if (static_cast<int>(i) == selectedIndex) {
            inventoryScreen += "> ";
        } else {
            inventoryScreen += "  ";
        }

        // item name padded to width
        std::size_t padding = (element.size() < 25) ? (25 - element.size()) : 1;
        inventoryScreen += element;
        inventoryScreen += std::string(padding, ' ');
        inventoryScreen += "x" + std::to_string(player.getItemCount(element)) + "\n";
    }
    inventoryScreen += "\n" + std::string(80, '-') + "\n";
    inventoryScreen += getSelectedItemDescription() + "\n";
	// not sure if needed: inventoryScreen += quantityprompt;
    std::cout << "\033[2J\033[H" << std::flush;
    std::cout << inventoryScreen << std::flush;
}

char InventoryUI::readKey() const {
	return static_cast<char>(_getch());
}
bool InventoryUI::isEscapeKey(char key) const {
	return key == 27;
}

bool InventoryUI::hasSelection() const {
	return selectedIndex >= 0 && selectedIndex < static_cast<int>(orderedItems.size());
}

std::string InventoryUI::getSelectedItemId() const {
	if (!hasSelection()) {
		return "";
	}
	return orderedItems[static_cast<size_t>(selectedIndex)];
}

std::string InventoryUI::getSelectedItemDescription() const {
	if (!hasSelection()) {
		return "No item selected.";
	}

	const std::string itemId = getSelectedItemId();
	ItemStats stats = ItemDatabase::getStats(itemId);
	return stats.description;
}

void InventoryUI::moveSelectionUp() {
	if (orderedItems.empty()) {
		selectedIndex = 0;
		return;
	}

	if (selectedIndex > 0) {
		--selectedIndex;
	}
}

void InventoryUI::moveSelectionDown() {
	if (orderedItems.empty()) {
		selectedIndex = 0;
		return;
	}

	const int lastIndex = static_cast<int>(orderedItems.size()) - 1;
	if (selectedIndex < lastIndex) {
		++selectedIndex;
	}
}

bool InventoryUI::handleActionKey(char key) {
	switch (key) {
        case 'k':
            moveSelectionUp();
            return false;  // navigation isn't an action, does not exit inventory
        case 'j':
            moveSelectionDown();
            return false;
		case 'u':
			useSelectedItem();
			return true;
		case 'd':
			dropSelectedItem();
			return true;
		case 'w':
			wieldWearSelectedItem();
			return true;
		default:
			return false;
	}
}

void InventoryUI::useSelectedItem() {
	// TODO: Implement item use effects.
	if (!hasSelection()) {
		pendingMessage = "No item selected.";
		return;
	}

	pendingMessage = "Use action not implemented yet for " + getSelectedItemId() + ".";
}

void InventoryUI::dropSelectedItem() {
	// TODO: Remove one item and set a message.
	if (!hasSelection()) {
		pendingMessage = "No item selected.";
		return;
	} else {
		int quantity = 1;
		const std::string itemId = getSelectedItemId();
		int max = player.getItemCount(itemId);
		if (max > 1) {
			std::cout << "Quantity to drop: " << std::endl;
			std::cin >> quantity;
			if (quantity<1 || quantity > max) {
				pendingMessage = "Enter stupid numbers, drop no stupid items.";
				return;
			}
		}
		player.removeItem(itemId, quantity);
		pendingMessage = "You drop ";
		if (quantity > 1) {
			pendingMessage += std::to_string(quantity) + " ";
		}
		pendingMessage += itemId + ". ";
		
	}
}
void InventoryUI::wieldWearSelectedItem() {
	// TODO: Check stats and equip if valid (damage => wield, armorBonus => wear).
	if (!hasSelection()) {
		pendingMessage = "No item selected.";
		return;
	}

	pendingMessage = "Wield/Wear action not implemented yet for " + getSelectedItemId() + ".";
}

std::string InventoryUI::run() {
    pendingMessage.clear();
    rebuildItemList();
    while (true) {
        render();
        char key = readKey();
        if (isEscapeKey(key)) {
            break;
        }
        if (handleActionKey(key)) break;
    }
    if (pendingMessage.empty()) {
        return "You check your inventory.";
    }
    return pendingMessage;
}

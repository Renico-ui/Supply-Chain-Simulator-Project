#include "Supplier.h"
#include <stdexcept>

Supplier::Supplier(int startingInventory) : inventory(startingInventory) {

    if(startingInventory < 0) {
        throw std::invalid_argument("Starting inventory cannot be below zero.");
    }
}

bool Supplier::supply(int amount) {
    if (amount <= inventory) {
        inventory -= amount;
        return true;
    }
    return false;
}

int Supplier::getInventory() const {
    return inventory;
}



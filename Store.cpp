#include "Store.h"
#include <stdexcept>

Store::Store(int startingInventory, int maxCapacity) : inventory(startingInventory), capacity(maxCapacity) {
    if (startingInventory < 0) {
        throw std::invalid_argument("Starting inventory cannot be negative.");
    }
    if (maxCapacity <= 0) {
        throw std::invalid_argument("Maximum capacity must be greater than zero.");
    }
    if (startingInventory > maxCapacity) {
        throw std::invalid_argument("Starting inventory cannot exceed maximum capacity.");
    }

}

bool Store::receiveProducts(int amount) {
    if (amount > 0 && (inventory + amount) <= capacity) {
        inventory += amount;
        return true;
    }
    return false;
}

bool Store::sellProducts(int amount) {
    if(amount > 0 && amount <= inventory ) {
        inventory -= amount;
        return true;
    }
    return false;
}

int Store::getInventory() const {
    return inventory;
}

int Store::getCapacity() const {
    return capacity;
}
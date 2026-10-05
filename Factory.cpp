#include "Factory.h"
#include <stdexcept>

Factory::Factory(int startingInventory, int startingRawMaterials, int maxCapacity)
    : inventory(startingInventory), rawMaterials(startingRawMaterials), capacity(maxCapacity) {

        if(startingInventory < 0) {
            throw std::invalid_argument("Starting inventory cannot be negative.");
        }
        if(startingRawMaterials < 0 || startingRawMaterials > maxCapacity) {
            throw std::invalid_argument("Starting raw materials must be between 0 and maximum capacity.");
        }
        if(maxCapacity <= 0) {
            throw std::invalid_argument("Maximum capacity must be greater than zero.");
        }
    }

bool Factory::receiveMaterials(int amount) {
    if(amount >0){
        rawMaterials += amount;
        return true;
    }
    return false;
}
bool Factory::sendProducts(int amount){
    if(amount > 0 && amount <= inventory){
        inventory -= amount;
        return true;
    }
    return false;
}

bool Factory::makeProduct(int amount) {
    if(amount > 0 && amount <= rawMaterials && (inventory + amount) <= capacity){
        rawMaterials -= amount;
        inventory += amount;
        return true;
    }
    return false;
}

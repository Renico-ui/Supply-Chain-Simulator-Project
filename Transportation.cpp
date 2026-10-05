#include "Transportation.h"
#include <stdexcept>

Transportation::Transportation(int maxCapacity, int currentCargo, int daysRemaining)
: capacity(maxCapacity), cargo(currentCargo), daysToArrive(daysRemaining) {

    if(maxCapacity <= 0) {
        throw std::invalid_argument("Capacity must be greater than zero.");
    }

    if(currentCargo < 0 || currentCargo > maxCapacity) {
        throw std::invalid_argument("Current cargo must be between 0 and capacity.");
    }

    if(daysRemaining < 0) {
        throw std::invalid_argument("Days to arrive cannot be negative.");
    }

}

bool Transportation::transport(int amount) {
    if(amount > 0 && (cargo + amount) <= capacity){
        cargo+= amount;
        return true;
    }
    return false;
}

void Transportation::transportDay() {
    if(daysToArrive > 0) {
        daysToArrive--;
    }
}

bool Transportation::unloadCargo(int amount) {
    if(amount > 0 && amount <= cargo) {
        cargo -= amount;
        return true;
    }
    return false;
}

bool Transportation::startTrip(int days) {
    if(days > 0 && hasArrived()) {
        daysToArrive = days;
        return true;
    }
    return false;
}
bool Transportation::hasArrived() const {
    return daysToArrive == 0;
}

int Transportation::getCapacity() const {
    return capacity;
}

int Transportation::getCargo() const {
    return cargo;
}

int Transportation::getDaysToArrive() const {
    return daysToArrive;
}

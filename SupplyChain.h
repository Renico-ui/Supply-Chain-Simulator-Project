#ifndef SUPPLYCHAIN_H
#define SUPPLYCHAIN_H

#include "Supplier.h"
#include "Factory.h"
#include "Transportation.h"
#include "Store.h"

#include <vector>
using namespace std;

enum class ShipmentDestination {
    None,
    Factory,
    Store
};

class SupplyChain {
    private:
        vector<Supplier> suppliers;
        vector<Factory> factories;
        vector<Transportation> transportations;
        vector<Store> stores;

        int currentDay;
        ShipmentDestination destination;
        int dailyDemand;
        int destinationIndex;

    public:
        SupplyChain();
        void simulateDay();

};

#endif
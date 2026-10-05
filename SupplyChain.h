#ifndef SUPPLYCHAIN_H
#define SUPPLYCHAIN_H

#include "Supplier.h"
#include "Factory.h"
#include "Transportation.h"
#include "Store.h"

enum class ShipmentDestination {
    None,
    Factory,
    Store
};

class SupplyChain {
    private:
        Supplier supplier;
        Factory factory;
        Transportation transportation;
        Store store;

        int currentDay;
        ShipmentDestination destination;
        int dailyDemand;
        
    public:
        SupplyChain();
        void simulateDay();

};

#endif
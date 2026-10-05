#include "SupplyChain.h"
#include "Supplier.h"
#include "Factory.h"
#include "Transportation.h"
#include "Store.h"
#include <stdexcept>
#include <iostream>
#include <string>
#include <algorithm>
#include <random>

using namespace std;

SupplyChain::SupplyChain() : 
supplier(100), 
factory(20, 50, 100), 
transportation(50, 0, 0), 
store(10, 100), 
currentDay(1), 
destination(ShipmentDestination::None) {}

void SupplyChain::simulateDay()
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distribution(1, 5);
    dailyDemand = distribution(gen);

    int sold = min(dailyDemand, store.getInventory());
    int unmetDemand = dailyDemand - sold;

    if (store.sellProducts(sold))
    {
    cout << "Day " << currentDay
         << ": Demand: " << dailyDemand
         << ", Sold: " << sold
         << ", Unmet demand: " << unmetDemand
         << ", Store inventory: " << store.getInventory()
         << endl;
    }

    transportation.transportDay();

    if (transportation.hasArrived() && destination == ShipmentDestination::Factory)
    {
        int cargo = transportation.getCargo();
        if (transportation.unloadCargo(cargo))
        {
            factory.receiveMaterials(cargo);
            cout << "Day " << currentDay << ": Shipment has arrived at Factory." << endl;

            if (factory.makeProduct(10))
            {
                cout << "Day " << currentDay
                     << ": Factory produced 10 products." << endl;

                if (factory.sendProducts(10))
                {
                    cout << "Sending to Store..." << endl;
                    transportation.transport(10);
                    transportation.startTrip(2);
                    destination = ShipmentDestination::Store;
                    cout << "Day " << currentDay << ": Shipment sent to the Store." << endl;
                }
            }
        }
    }
        if (!transportation.hasArrived() &&
            destination == ShipmentDestination::Factory)
        {

            cout << "Day " << currentDay
                 << ": Shipment is traveling. "
                 << transportation.getDaysToArrive()
                 << " days remaining." << endl;
        }

        if (transportation.hasArrived() && destination == ShipmentDestination::Store)
        {
            int cargo = transportation.getCargo();
            if (transportation.unloadCargo(cargo))
            {
                if (store.receiveProducts(cargo))
                {
                    cout << "Day " << currentDay << ": Shipment has arrived at Store." << endl;
                    destination = ShipmentDestination::None;
                    
                }
            }
        }

        if (!transportation.hasArrived() &&
            destination == ShipmentDestination::Store)
        {

            cout << "Day " << currentDay
                 << ": Shipment is traveling to Store. "
                 << transportation.getDaysToArrive()
                 << " days remaining." << endl;
        }


        if (destination == ShipmentDestination::None &&
            transportation.getCargo() == 0)
        {
            if (supplier.supply(10))
            {
                cout << "Supplier supplied 10 to factory!!" << endl;

                transportation.transport(10);
                transportation.startTrip(2);

                destination = ShipmentDestination::Factory;

                cout << "Day " << currentDay
                     << ": Shipment is sent to Factory." << endl;
            }
        }

        currentDay++;
    }


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
#include <vector>

using namespace std;

SupplyChain::SupplyChain() :
    currentDay(1),
    destination(ShipmentDestination::None),
    destinationIndex(-1)
{
    suppliers.emplace_back(100);
    suppliers.emplace_back(150);
    suppliers.emplace_back(200);

    factories.emplace_back(20, 50, 100);
    factories.emplace_back(30, 75, 150);

    stores.emplace_back(10, 100);
    stores.emplace_back(15, 150);
    stores.emplace_back(20, 200);

    transportations.emplace_back(50, 0, 0);
}

void SupplyChain::simulateDay()
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distribution(1, 5);

    // Handle customer demand at every store
    for (auto& store : stores)
    {
        int demand = distribution(gen);
        int sold = min(demand, store.getInventory());
        int unmetDemand = demand - sold;

        if (store.sellProducts(sold))
        {
            cout << "Day " << currentDay
                 << ": Demand: " << demand
                 << ", Sold: " << sold
                 << ", Unmet demand: " << unmetDemand
                 << ", Store inventory: " << store.getInventory()
                 << endl;
        }
    }

    // Move the current shipment
    transportations[0].transportDay();

    // Check whether a shipment has arrived at a factory
    for (int i = 0; i < factories.size(); i++)
    {
        if (transportations[0].hasArrived() &&
            destination == ShipmentDestination::Factory &&
            destinationIndex == i)
        {
            Factory& factory = factories[i];

            int cargo = transportations[0].getCargo();

            if (transportations[0].unloadCargo(cargo))
            {
                factory.receiveMaterials(cargo);

                cout << "Day " << currentDay
                     << ": Shipment has arrived at Factory "
                     << i << "." << endl;

                if (factory.makeProduct(10))
                {
                    cout << "Day " << currentDay
                         << ": Factory produced 10 products." << endl;

                    if (factory.sendProducts(10))
                    {
                        cout << "Sending to Store..." << endl;

                        transportations[0].transport(10);
                        transportations[0].startTrip(2);

                        destination = ShipmentDestination::Store;
                        destinationIndex = 0;

                        cout << "Day " << currentDay
                             << ": Shipment sent to Store "
                             << destinationIndex << "." << endl;

                        break;
                    }
                }
            }
        }
    }

    // Shipment is traveling to a factory
    if (!transportations[0].hasArrived() &&
        destination == ShipmentDestination::Factory)
    {
        cout << "Day " << currentDay
             << ": Shipment is traveling. "
             << transportations[0].getDaysToArrive()
             << " days remaining." << endl;
    }

    // Check whether a shipment has arrived at a store
    for (int i = 0; i < stores.size(); i++)
    {
        if (transportations[0].hasArrived() &&
            destination == ShipmentDestination::Store &&
            destinationIndex == i)
        {
            Store& store = stores[i];

            int cargo = transportations[0].getCargo();

            if (transportations[0].unloadCargo(cargo))
            {
                if (store.receiveProducts(cargo))
                {
                    cout << "Day " << currentDay
                         << ": Shipment has arrived at Store "
                         << i << "." << endl;

                    destination = ShipmentDestination::None;
                    destinationIndex = -1;

                    break;
                }
            }
        }
    }

    // Shipment is traveling to a store
    if (!transportations[0].hasArrived() &&
        destination == ShipmentDestination::Store)
    {
        cout << "Day " << currentDay
             << ": Shipment is traveling to Store. "
             << transportations[0].getDaysToArrive()
             << " days remaining." << endl;
    }

    // If there is no current shipment, a supplier can send one
    for (auto& supplier : suppliers)
    {
        if (destination == ShipmentDestination::None &&
            transportations[0].getCargo() == 0)
        {
            if (supplier.supply(10))
            {
                cout << "Supplier supplied 10 to factory!!" << endl;

                transportations[0].transport(10);
                transportations[0].startTrip(2);

                destination = ShipmentDestination::Factory;
                destinationIndex = 0;

                cout << "Day " << currentDay
                     << ": Shipment is sent to Factory "
                     << destinationIndex << "." << endl;

                break;
            }
        }
    }

    currentDay++;
}

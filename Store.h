#ifndef STORE_H
#define STORE_H

class Store {
    private:
        int inventory;
        int capacity;

    public:
        Store(int startingInventory, int maxCapacity);

        bool receiveProducts(int amount);
        bool sellProducts(int amount);
        int getInventory() const;
        int getCapacity() const;
};

#endif
#ifndef FACTORY_H
#define FACTORY_H

class Factory {
    private:
        int rawMaterials;
        int inventory;
        int capacity;
    public:
        Factory(int startingInventory, int startingRawMaterials, int maxCapacity);

        bool receiveMaterials(int amount);
        bool sendProducts(int amount);
        bool makeProduct(int amount);

        int getRawMaterials() const;
        int getInventory() const; 
        int getCapacity() const;

};

#endif
#ifndef SUPPLIER_H
#define SUPPLIER_H

class Supplier {
    private:
        int inventory;
    public:
        Supplier(int startingInventory);

        bool supply(int amount);
        int getInventory() const;

};

#endif 
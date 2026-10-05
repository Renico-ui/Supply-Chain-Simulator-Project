#ifndef TRANSPORTATION_H
#define TRANSPORTATION_H

class Transportation {
    private:
        int capacity;
        int cargo;
        int daysToArrive;

    public:
        Transportation(int maxCapacity, int currentCargo, int daysRemaining);

        bool transport(int amount);
        void transportDay();
        bool hasArrived() const; 
        bool unloadCargo(int amount);
        bool startTrip(int days);

        int getCapacity() const;
        int getCargo() const;
        int getDaysToArrive() const;


};

#endif
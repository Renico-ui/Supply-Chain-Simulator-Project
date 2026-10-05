#include "SupplyChain.h"

int main() {

    SupplyChain supplyChain;

    for (int i = 0; i < 10; i++) {
        supplyChain.simulateDay();
    }

    return 0;
}
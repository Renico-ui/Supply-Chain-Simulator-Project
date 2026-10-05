#include "SupplyChain.h"

int main() {

    SupplyChain supplyChain;

    for (int i = 0; i < 30; i++) {
        supplyChain.simulateDay();
    }

    return 0;
}
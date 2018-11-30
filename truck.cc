#include "truck.h"
#include "printer.h"
#include "nameServer.h"
#include "bottlingPlant.h"
#include "MPRNG.h"

using namespace std;

extern MPRNG mprng;

Truck::Truck( Printer & prt, NameServer & nameServer, BottlingPlant & plant,
    unsigned int numVendingMachines, unsigned int maxStockPerFlavour )
        : printer(prt), nameServer(nameServer), plant(plant),
        numVendingMachines(numVendingMachines), maxStockPerFlavour(maxStockPerFlavour) {
    
}

bool Truck::isEmpty( unsigned int cargo[] ) {
    for ( unsigned int i = 0; i < 4; i++ ) {
        if ( 0 < cargo[i] ) return false;
    } // for
    return true;
}

void Truck::main() {
    unsigned int cargo[4] = { 0, 0, 0, 0 };
    VendingMachine** vms = nameServer.getMachineList();
    unsigned int lastVm = numVendingMachines - 1;

    while (true) {
        try {
            yield( mprng( 1, 10 ) );
            plant.getShipment( cargo );

            for ( unsigned int i = 0; i < numVendingMachines; i++  ) {
                lastVm++;
                lastVm %= numVendingMachines;
                unsigned int* inv = vms[lastVm]->inventory();
                for ( unsigned int i = 0; i < 4; i++ ) {
                    unsigned int restock = maxStockPerFlavour - inv[i];
                    if ( restock <= cargo[i] ) {
                        cargo[i] -= restock;
                        inv[i] += restock;
                    } // if
                } // for
                
                if ( isEmpty( cargo ) ) {
                    break;
                } // if
            } // for
        } catch( BottlingPlant::Shutdown& ) {
            break;
        } // try
    } // while
}

#include "truck.h"
#include "printer.h"
#include "nameServer.h"
#include "bottlingPlant.h"
#include "vendingMachine.h"
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
    printer.print(Printer::Truck, 'S');

    unsigned int cargo[4] = { 0, 0, 0, 0 };
    VendingMachine** vms = nameServer.getMachineList();
    unsigned int lastVm = numVendingMachines - 1;

    while (true) {
        try {
            yield( mprng( 1, 10 ) );
            plant.getShipment( cargo );

            unsigned int totalProduced = 0;
            for ( unsigned int i = 0; i < 4; i++ ) {
                totalProduced += cargo[i];
            }

            printer.print( Printer::Truck, 'P', totalProduced );

            for ( unsigned int i = 0; i < numVendingMachines; i++  ) {         
                if ( isEmpty( cargo ) ) {
                    break;
                } // if

                lastVm++;
                lastVm %= numVendingMachines;
                VendingMachine* vm = vms[lastVm];
                unsigned int* inv = vm->inventory();
                unsigned int vmId = vm->getId();

                printer.print( Printer::Truck, 'd', vmId, totalProduced ); 

                unsigned int notFilled = 0;
                for ( unsigned int i = 0; i < 4; i++ ) {
                    unsigned int restock = min(maxStockPerFlavour - inv[i], cargo[i]);
                    cargo[i] -= restock;
                    totalProduced -= restock;
                    inv[i] += restock;
                    notFilled += (maxStockPerFlavour - inv[i]);
                } // for

                vms[lastVm]->restocked();

                if ( notFilled > 0 ) {
                    printer.print( Printer::Truck, 'U', vmId, notFilled );
                } // if
                printer.print( Printer::Truck, 'D', vmId, totalProduced );
            } // for
        } catch( BottlingPlant::Shutdown& ) {
            break;
        } // try
    } // while
    printer.print(Printer::Truck, 'F');
}

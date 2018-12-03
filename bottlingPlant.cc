#include "bottlingPlant.h"
#include "printer.h"
#include "nameServer.h"
#include "truck.h"
#include "MPRNG.h"

extern MPRNG mprng;

using namespace std;

BottlingPlant::BottlingPlant( Printer & prt, NameServer & nameServer, unsigned int numVendingMachines,
        unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour, unsigned int timeBetweenShipments ) 
            : printer(prt), nameServer(nameServer), numVendingMachines(numVendingMachines),
            maxShippedPerFlavour(maxShippedPerFlavour), maxStockPerFlavour(maxStockPerFlavour), 
            timeBetweenShipments(timeBetweenShipments), timeToShut(false) {}

BottlingPlant::~BottlingPlant() {
}

void BottlingPlant::getShipment( unsigned int cargo[ ] ) {
    if ( timeToShut ) {
        uRendezvousAcceptor();
        _Throw Shutdown();
    } // if

    for ( unsigned int i = 0; i < 4; i++ ) {
        cargo[i] = production[i];
    } // for
}

void BottlingPlant::main() {
    printer.print(Printer::BottlingPlant, 'S');
    Truck truck( printer, nameServer, *this, numVendingMachines, maxStockPerFlavour );

    while (true) {
        unsigned int totalProduced = 0;
        for ( unsigned int i = 0; i < 4; i++ ) {
            production[i] = mprng( maxShippedPerFlavour );
            totalProduced += production[i];
        } // for
        
        printer.print(Printer::BottlingPlant, 'G', totalProduced);
        yield( timeBetweenShipments );

        _Accept( ~BottlingPlant ) {
            timeToShut = true;
            _Accept( getShipment );     // final shipment
            break;
        } or _Accept( getShipment ) {
            fill(begin(production), end(production), 0);
            printer.print(Printer::BottlingPlant, 'P');
        } // _Accept
    } // while

    printer.print(Printer::BottlingPlant, 'F');
}

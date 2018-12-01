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
            timeBetweenShipments(timeBetweenShipments), timeToShut(false) {
    production = { 0, 0, 0, 0 };
}

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

    printer.print(Printer::BottlingPlant, 'P');
}

void BottlingPlant::main() {
    printer.print(Printer::BottlingPlant, 'S');
    Truck truck( printer, nameServer, *this, numVendingMachines, maxStockPerFlavour );

    while (true) {
        unsigned int numGen = 0;
        for ( unsigned int i = 0; i < 4; i++ ) {
            production[i] = mprng( maxShippedPerFlavour );
            numGen += production[i];
        } // for
        printer.print(Printer::BottlingPlant, 'G', numGen);
        yield( timeBetweenShipments );

        _Accept( ~BottlingPlant ) {
            timeToShut = true;
            break;
        } or _Accept( getShipment ) {
            production = { 0, 0, 0, 0 };
        } // _Accept
    } // while

    try {
        _Accept( getShipment ); // final shipment call
    } catch ( uMutexFailure::RendezvousFailure ) {}

    printer.print(Printer::BottlingPlant, 'F');
}

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
        _Throw Shutdown();
    } // if

    for ( unsigned int i = 0; i < 4; i++ ) {
        cargo[i] = production[i];
    } // for
}

bool BottlingPlant::hasProduction() {
    for ( unsigned int i = 0; i < 4; i++ ) {
        if ( 0 < production[i] ) return false;
    } // for
    return true;
}

void BottlingPlant::main() {
    Truck truck( printer, nameServer, *this, numVendingMachines, maxStockPerFlavour );

    while (true) {
        for ( unsigned int i = 0; i < 4; i++ ) {
            production[i] = mprng( maxShippedPerFlavour );
        } // for
        yield( timeBetweenShipments );

        _Accept( ~BottlingPlant ) {
            timeToShut = true;
            break;
        } or _Accept( getShipment ) {
            production = { 0, 0, 0, 0 };
        } // _Accept
    } // while
}

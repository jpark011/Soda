#include "bottlingPlant.h"
#include "printer.h"
#include "nameServer.h"
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
        production[i] = 0;
    } // for
}

bool BottlingPlant::hasProduction() {
    for ( unsigned int i = 0; i < 4; i++ ) {
        if ( 0 < production[i] ) return false;
    } // for
    return true;
}

void BottlingPlant::main() {
    while (true) {
        _Accept( ~BottlingPlant ) {
            timeToShut = true;
            break;
        }
        _When( hasProduction ) _Accept( getShipment ) {
        } // _Accept
        for ( unsigned int i = 0; i < 4; i++ ) {
            production[i] = mprng( maxStockPerFlavour );
        } // for

        yield( timeBetweenShipments );
    } // while
}

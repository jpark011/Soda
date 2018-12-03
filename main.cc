#include <iostream>
using namespace std;					// direct access to std
#include "MPRNG.h"
#include <cstdlib>					// exit
#include "config.h"
#include "printer.h"
#include "bank.h"
#include "parent.h"
#include "groupoff.h"
#include "watcardOffice.h"
#include "nameServer.h"
#include "vendingMachine.h"
#include "student.h"
#include "bottlingPlant.h"
// global definition
MPRNG mprng;

void usage( char * argv[] ) {
    cerr << "Usage: " << argv[0]
	 << " [ config-file [ Seed ] ]" << endl;
    exit( EXIT_FAILURE );				// TERMINATE
} // usage

int main( int argc, char * argv[] ) {
    string configFile = "soda.config";
    int seed = getpid(),
        processors = 1;

    try {
        switch ( argc ) {
            case 3: 
                configFile = string( argv[2] );
            case 2: 
                seed = stoi( argv[1] );
                if ( seed <= 0 ) throw 1; 
            case 1:
                break;
            default: 					// wrong number of options
                throw 1;
        } // switch
    } catch (...) {
        usage(argv);
    } // try
    mprng.set_seed(seed);
    if ( 1 < processors ) {
        uProcessor p[processors - 1] __attribute__(( unused ));
    }

    ConfigParms config;
    processConfigFile( configFile.c_str(), config );

    Printer printer( config.numStudents, config.numVendingMachines, config.numCouriers );
    Bank bank( config.numStudents );
    Parent parent( printer, bank, config.numStudents, config.parentalDelay );
    Groupoff groupoff( printer, config.numStudents, config.sodaCost, config.groupoffDelay );
    WATCardOffice office( printer, bank, config.numCouriers );
    NameServer ns( printer, config.numVendingMachines, config.numStudents );
    VendingMachine* vms[ config.numVendingMachines ];
    for ( unsigned int i = 0; i < config.numVendingMachines; i++ ) {
        vms[i] = new VendingMachine( printer, ns, i, config.sodaCost );
    } // for
 {
    BottlingPlant plant( printer, ns, config.numVendingMachines, config.maxShippedPerFlavour, config.maxStockPerFlavour, config.timeBetweenShipments );
    Student* students[ config.numStudents ];
    for ( unsigned int i = 0; i < config.numStudents; i++ ) {
        students[i] = new Student( printer, ns, office, groupoff, i, config.maxPurchases );
    } // for

    for ( unsigned int i = 0; i < config.numStudents; i++ ) {
        delete students[i];
    } // for
}
    for ( unsigned int i = 0; i < config.numVendingMachines; i++ ) {
        delete vms[i];
    } // for
} // main

#include "vendingMachine.h"
#include <algorithm>
#include "printer.h"
#include "nameServer.h"
#include "watcard.h"
#include "MPRNG.h"

extern MPRNG mprng;

using namespace std;

VendingMachine::VendingMachine( Printer & prt, NameServer & nameServer, unsigned int id, unsigned int sodaCost )
        : printer(prt), nameServer(nameServer), id(id), sodaCost(sodaCost) {
    fill_n( inventories, NUM_FLAVOURS, 0 );
    nameServer.VMregister( this );
}

VendingMachine::~VendingMachine() {

}

void VendingMachine::buy( VendingMachine::Flavours flavour, WATCard & card ) {
    if ( card.getBalance() < cost() ) {
        _Throw Funds();
    } // if

    if ( inventories[flavour] <= 0 ) {
        _Throw Stock();
    } // if

    didBuy = true;
    if ( mprng(4) == 0 ) {
        _Throw Free();
    } // if

    card.withdraw( cost() );
    lastFlavour = flavour;
}

unsigned int* VendingMachine::inventory() {
    return inventories;
}

void VendingMachine::restocked() {
}

_Nomutex unsigned int VendingMachine::cost() {
    return sodaCost;
}

_Nomutex unsigned int VendingMachine::getId() {
    return id;
}

void VendingMachine::main() {
    printer.print( Printer::Vending, id, 'S' );
    while (true) {
        try {
            _Accept ( ~VendingMachine ) {
                break;
            } or _Accept( buy ) {
                if ( didBuy ) {
                    inventories[lastFlavour]--;
                    printer.print( Printer::Vending, id, 'B', lastFlavour, inventories[lastFlavour] );
                } // if
                didBuy = false;
            } or _Accept( inventory ) {
                printer.print( Printer::Vending, id, 'r' );
                _Accept( restocked ); // _Accept
                printer.print( Printer::Vending, id, 'R' );
            } // _Accept
        } catch ( uMutexFailure::RendezvousFailure ) {
        } // try
    } // while
    printer.print( Printer::Vending, id, 'F' );
}

#include "vendingMachine.h"
#include "printer.h"
#include "nameServer.h"
#include "watcard.h"
#include "MPRNG.h"

extern MPRNG mprng;

using namespace std;

VendingMachine::VendingMachine( Printer & prt, NameServer & nameServer, unsigned int id, unsigned int sodaCost, unsigned int maxStockPerFlavour )
        : printer(prt), nameServer(nameServer), id(id), sodaCost(sodaCost), maxStockPerFlavour(maxStockPerFlavour) {
    inventories = { 0, 0, 0, 0 };
    nameServer.VMregister( this );
}

void VendingMachine::buy( VendingMachine::Flavours flavour, WATCard & card ) {
        if ( card.getBalance() < cost() ) {
            _Throw Funds();
        } // if

        if ( inventories[flavour] <= 0 ) {
            _Throw Stock();
        } // if

        if ( prng(4) == 0 ) {
            _Throw Free();
        } // if

        card.withdraw( cost() );
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
    _Accept( buy ) {

    } or _Accept( inventory ) {
        _Accept( restocked ) {
        } // _Accept
    } // _Accept
}

#include "vendingMachine.h"
#include <algorithm>
#include "printer.h"
#include "nameServer.h"
#include "watcard.h"
#include "MPRNG.h"

extern MPRNG mprng;

using namespace std;

/*********** VendingMachine ***********
    * Purpose: A task that recives drink orders from students
    * 
    * Returns: void
    * 
    * Parameters:
    *       prt         - printer
    *       nameServer - name server
    *       id - vm id
*           sodaCost - cost for a drink
    * 
    * Errors: No errors
    * 
    * Globals: N/A
***************************************/
VendingMachine::VendingMachine( Printer & prt, NameServer & nameServer, unsigned int id, unsigned int sodaCost )
        : printer(prt), nameServer(nameServer), id(id), sodaCost(sodaCost) {
    fill_n( inventories, NUM_FLAVOURS, 0 );
    nameServer.VMregister( this );
}

VendingMachine::~VendingMachine() {

}

/*********** buy ***********
    * Purpose: buy a drink
    * 
    * Returns: void
    * 
    * Parameters:
    *       flavour - drink flavour
    *       card - card to charge
    * 
    * Errors: 
    *       Funds - not enough balance
    *       Stock - out of stock
    *       Free - free drink
    * 
    * Globals: N/A
***************************************/
void VendingMachine::buy( VendingMachine::Flavours flavour, WATCard & card ) {
    if ( card.getBalance() < cost() ) {
        _Throw Funds();
    } // if

    if ( inventories[flavour] <= 0 ) {
        _Throw Stock();
    } // if
    lastFlavour = flavour;
    didBuy = true;
    if ( mprng(4) == 0 ) {
        _Throw Free();
    } // if

    card.withdraw( cost() );
}

/*********** inventory ***********
    * Purpose: get inventory of vm 
    * 
    * Returns:
    *       unsigned int* - inventory pointer
    * 
    * Parameters: N/A
    * 
    * Errors: N/A 
    * 
    * Globals: N/A
***************************************/
unsigned int* VendingMachine::inventory() {
    return inventories;
}

/*********** restocked ***********
    * Purpose: called when vm is restocked 
    * 
***************************************/
void VendingMachine::restocked() {
}

/*********** cost ***********
    * Purpose: get cost of a drink  
    * 
    * Returns:
    *       unsigned int - cost of drink
    * 
    * Parameters: N/A
    * 
    * Errors: N/A 
    * 
    * Globals: N/A
***************************************/
_Nomutex unsigned int VendingMachine::cost() {
    return sodaCost;
}

/*********** getId ***********
    * Purpose: get id of vm   
    * 
    * Returns:
    *       unsigned int - id of drink
    * 
    * Parameters: N/A
    * 
    * Errors: N/A 
    * 
    * Globals: N/A
***************************************/
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

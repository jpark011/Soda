#include "student.h"
#include "printer.h"
#include "nameServer.h"
#include "watcardOffice.h"
#include "groupoff.h"
#include "watcard.h"
#include "vendingMachine.h"
#include "MPRNG.h"

using namespace std;

extern MPRNG mprng;

Student::Student( Printer & prt, NameServer & nameServer, WATCardOffice & cardOffice, 
        Groupoff & groupoff, unsigned int id, unsigned int maxPurchases )
    : printer(prt), nameServer(nameServer), watcardOffice(cardOffice), groupoff(groupoff), id(id), maxPurchases(maxPurchases) {

}

void Student::main() {
    const unsigned int NUM_FLAVORS = VendingMachine::NUM_FLAVOURS;
    const unsigned int INIT_BALANCE = 5;

    unsigned int numPurchases = mprng(1, maxPurchases);
    unsigned int favSoda = mprng( NUM_FLAVORS - 1 ); 

    WATCard::FWATCard watcard = watcardOffice.create( id, INIT_BALANCE );
    WATCard::FWATCard giftcard = groupoff.giftCard();

    printer.print( Printer::Student, id, 'S' );

    VendingMachine* vm = nameServer.getMachine( id );;
    printer.print( Printer::Student, id, 'V', vm->getId() );

    for ( unsigned int i = 0; i < numPurchases; i++ ) {
        yield( mprng(1, 10) );      // wait before buy
        while (true) {
            try {
                _Select( watcard ) {
                    try {
                        vm->buy( (VendingMachine::Flavours) favSoda, *watcard );
                        printer.print( Printer::Student, id, 'B', favSoda, watcard()->getBalance() );
                    } catch ( VendingMachine::Free& ) {
                        printer.print( Printer::Student, id, 'A', favSoda, watcard()->getBalance() );
                        yield( 4 );
                    } // try
                } or _Select( giftcard ) {
                    try {
                        vm->buy( (VendingMachine::Flavours) favSoda, *giftcard );
                        printer.print( Printer::Student, id, 'G', favSoda, giftcard()->getBalance() );
                        giftcard.reset();
                    } catch ( VendingMachine::Free& ) {
                        printer.print( Printer::Student, id, 'a', favSoda, giftcard()->getBalance() );
                        yield( 4 );
                    } // try
                } // _Select
                // bought a soda!
                break;
            } catch ( VendingMachine::Funds& ) {
                unsigned int fundToAdd = INIT_BALANCE + vm->cost();
                watcardOffice.transfer( id, fundToAdd , watcard() );
            } catch ( VendingMachine::Stock& ) {
                vm = nameServer.getMachine( id );;
            } catch ( WATCardOffice::Lost& ) {
                printer.print( Printer::Student, id, 'L' );
                watcard = watcardOffice.create( id, INIT_BALANCE );
            }// try
        } // while
    } // for
    delete watcard();
    delete giftcard();
    printer.print( Printer::Student, id, 'F' );
}

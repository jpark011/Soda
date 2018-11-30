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
    const unsigned int NUM_FLAVORS = 4;
    const unsigned int INIT_BALANCE = 5;

    unsigned int numPurchases = mprng(1, maxPurchases);
    unsigned int favSoda = mprng( NUM_FLAVORS - 1 ); 

    WATCard::FWATCard watcard = watcardOffice.create( id, INIT_BALANCE );
    WATCard::FWATCard giftcard = groupoff.giftcard();

    VendingMachine* vm = nameServer.getMachine( id );;

    for ( unsigned int i = 0; i < numPurchases; i++ ) {
        yield( mprng(1, 10) );      // wait before buy
        while (true) {
            try {
                _Select( watcard ) {
                    vm->buy( (VendingMachine::Flavours) favSoda, *watcard );
                } or _Select( giftcard ) {
                    vm->buy( (VendingMachine::Flavours) favSoda, *giftcard );
                    giftcard.reset();
                }
                // bought a soda!
                break;
            } catch ( VendingMachine::Free& ) {
                yield(4);
                // free soda!
                break;                    
            } catch ( VendingMachine::Funds& ) {
                unsigned int fundToAdd = INIT_BALANCE + vendings[j]->cost();
                watcardOffice.transfer( id, fundToAdd , &watcard );
            } catch ( VendingMachine::Stock& ) {
                vm = nameServer.getMachine( id );;
            } catch ( WATCardOffice::Lost& ) {
                watcard = watcardOffice.create( id, INIT_BALANCE );
            }// try
        } // while
    } // for
}

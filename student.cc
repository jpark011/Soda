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
    const unsigned int NUM_FLAVORS = 3;
    const unsigned int INIT_BALANCE = 5;

    unsigned int numPurchases = mprng(1, maxPurchases);
    unsigned int favSoda = mprng( NUM_FLAVORS ); 

    WATCard::FWATCard watcard = watcardOffice.create( id, INIT_BALANCE );
    WATCard::FWATCard giftcard = groupoff.giftcard();

    VendingMachine* vendings[] = nameServer.getMachineList();

    for ( unsigned int i = 0; i < numPurchases; i++ ) {
        try {
            yield( mprng(1, 10) );      // wait before buy
            if () { // if watcard is lost
                watcard = watcardOffice.create( id, INIT_BALANCE );
            } // if

            unsigned int j = 0;     // iterate vending machines
            while (true) {
                try {
                    vendings[j]->buy( (VendingMachine::Flavours) favSoda,
                        watcard );
                    break;
                } catch ( VendingMachine::Free& ) {
                    yield(4);
                    break;                    
                } catch ( VendingMachine::Funds& ) {
                    unsigned int fundToAdd = INIT_BALANCE + vendings[j]->cost();
                    watcardOffice.transfer( id, fundToAdd , &watcard );
                } catch ( VendingMachine::Stock& ) {
                    j++;
                    j %= vendings.length; 
                } // try
            } // while
        } catch ( WATCardOffice::Lost& ) {
            watcard = 
        } // try
    } // for
}

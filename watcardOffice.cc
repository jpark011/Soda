#include "watcardOffice.h"
#include "printer.h"
#include "bank.h"

using namespace std;

extern MPRNG mprng;

WATCardOffice::WATCardOffice( Printer & prt, Bank & bank, unsigned int numCouriers )
                : printer(prt), bank(bank),  numCouriers(numCouriers) {
    for ( unsigned int i = 0; i < numCouriers; i++ ) {
        couriers.push_back( WATCardOffice::Courier( *this ) );
    } // for
}

WATCard::FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount ) {
}

WATCard::FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard *card ) {
}

Job* WATCardOffice::requestWork() {

}

void WATCardOffice::main() {

}

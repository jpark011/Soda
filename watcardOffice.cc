#include "watcardOffice.h"
#include "printer.h"
#include "bank.h"
#include "MPRNG.h"

using namespace std;

extern MPRNG mprng;

WATCardOffice::WATCardOffice( Printer & prt, Bank & bank, unsigned int numCouriers )
                : printer(prt), bank(bank),  numCouriers(numCouriers) {
    for ( unsigned int i = 0; i < numCouriers; i++ ) {
        couriers.push_back( new WATCardOffice::Courier( printer, *this, bank ) );
    } // for
}

WATCardOffice::~WATCardOffice() {
    for ( auto courier = couriers.begin(); i != couriers.end(); i++ ) {
        delete *courier;
    } // for

    for ( auto job = jobs.begin(); i != jobs.end(); i++ ) {
        (*job)->result.cancel();
        delete *job;
    } // for
}

WATCard::FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount ) {
    Job* newJob = new Job( { sid, amount } );
    jobs.push_back( newJob );

    return newJob->result;
}

WATCard::FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard *card ) {
    Job* newJob = new Job( { sid, amount, card } );
    jobs.push_back( newJob );

    return newJob->result;
}

Job* WATCardOffice::requestWork() {
    return jobs.front();
}

void WATCardOffice::main() {
    while (true) {
        _Accept( ~WATCardOffice ) {
            break;
        } or _Accept( create, transfer ) {
        } or _When( !jobs.empty() ) _Accept( requestWork ) {
            jobs.pop_front();
        } // _Accept
    } // while
}

#include "watcardOffice.h"
#include "printer.h"
#include "bank.h"
#include "MPRNG.h"

using namespace std;

extern MPRNG mprng;

/*********** WATCardOffice ***********
    * Purpose: Administrator managing WATCard and students
    * 
    * Returns: void
    * 
    * Parameters:
    *       prt         - printer
    *       bank - bank
    *       numCouriers - number of couriers
    * 
    * Errors: No errors
    * 
    * Globals: N/A
***************************************/
WATCardOffice::WATCardOffice( Printer & prt, Bank & bank, unsigned int numCouriers )
                : printer(prt), bank(bank),  numCouriers(numCouriers) {
    for ( unsigned int i = 0; i < numCouriers; i++ ) {
        couriers.push_back( new WATCardOffice::Courier( printer, *this, bank, i ) );
    } // for
}

WATCardOffice::~WATCardOffice() {
    for ( auto courier = couriers.begin(); courier != couriers.end(); courier++ ) {
        delete *courier;
    } // for
    while ( !jobs.empty() ) {
        Job * job = jobs.front();
        jobs.pop();
        job->result.cancel();
        delete job;
    } // while
}

/*********** create ***********
    * Purpose: create WATCard
    * 
    * Returns:
    *       FWARCard - watcard (as future)
    * 
    * Parameters:
    *       sid - student id
    *       amout - init balance
    * 
    * Errors: N/A 
    *   
    * Globals: N/A
***************************************/
WATCard::FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount ) {
    Job* newJob = new Job( { sid, amount } );
    jobs.push( newJob );

    return newJob->result;
}

/*********** transfer ***********
    * Purpose: add balance to WATCard
    * 
    * Returns:
    *       FWARCard - watcard (as future)
    * 
    * Parameters:
    *       sid - student id
    *       amoumt - balance to add
    *       watcard - WATCard
    * 
    * Errors: N/A 
    *   
    * Globals: N/A
***************************************/
WATCard::FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard *card ) {
    Job* newJob = new Job( { sid, amount, card } );
    jobs.push( newJob );

    return newJob->result;
}

/*********** reuqestWork ***********
    * Purpose: get next job
    * 
    * Returns:
    *       Job - next job
    * 
    * Parameters: N/A
    * 
    * Errors: N/A 
    *   
    * Globals: N/A
***************************************/
WATCardOffice::Job* WATCardOffice::requestWork() {
    if ( jobs.empty() ) {   // final work
        return nullptr;
    } // if
    return jobs.front();
}

void WATCardOffice::main() {
    printer.print( Printer::WATCardOffice, 'S' );
    while (true) {
        _Accept( ~WATCardOffice ) {
            while ( 0 < numCouriers ) {
                _Accept( requestWork ) ;     // final work
                numCouriers--;
            }
            break;
        } or _Accept( create ) {
            Args args = jobs.front()->args; 
            printer.print( Printer::WATCardOffice, 'C', args.stdId, args.fund );
        } or _Accept( transfer ) {
            Args args = jobs.front()->args; 
            printer.print( Printer::WATCardOffice, 'T', args.stdId, args.fund );
        } or _When( !jobs.empty() ) _Accept( requestWork ) {
            jobs.pop();
            printer.print( Printer::WATCardOffice, 'W' );
        } // _Accept
    } // while
    printer.print( Printer::WATCardOffice, 'F' );
}

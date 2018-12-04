#include "watcardOffice.h"
#include "MPRNG.h"
#include "bank.h"
#include "printer.h"

using namespace std;

extern MPRNG mprng; 

WATCardOffice::Courier::Courier( Printer& printer, WATCardOffice& watcardOffice, Bank& bank, unsigned int id )
        : printer(printer), watcardOffice(watcardOffice), bank(bank), id(id) {
}

WATCardOffice::Courier::~Courier() {

}

void WATCardOffice::Courier::main() {
    printer.print( Printer::Courier, id, 'S' );
    while (true) {
        _Accept( ~Courier ) {
            break;
        } _Else {
            WATCardOffice::Job* job = watcardOffice.requestWork();
            if ( job == nullptr ) {     // office closed
                break;
            } // if
            unsigned int stdId = job->args.stdId;
            unsigned int fund = job->args.fund;
            WATCard* watcard = job->args.watcard;
            
            if ( watcard == nullptr ) {
                watcard = new WATCard();
            } // if

            printer.print( Printer::Courier, id, 't', stdId, fund );
            bank.withdraw( stdId, fund );
            watcard->deposit( fund );
            if ( mprng( 5 ) == 0 ) {    // lost
                job->result.exception( new Lost );
                printer.print( Printer::Courier, id, 'L', stdId );
            } else {        // deposit success
                job->result.delivery( watcard );
                printer.print( Printer::Courier, id, 'T', stdId, fund );
            } // if
            delete job;     // job done
        } // _Accept
    } // while
    printer.print( Printer::Courier, id, 'F' );
}

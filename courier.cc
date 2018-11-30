#include "watcardOffice.h"
#include "MPRNG.h"

using namespace std;

extern MPRNG mprng; 

WATCardOffice::Courier::Courier( Printer& printer, WATCardOffice& watcardOffice, Bank& bank ) 
        : printer(printer), watcardOFfice(watcardOFfice), bank(bank) {
}

WATCardOffice::Courier::~Courier() {

}

void WATCardOffice::Courier::main() {
    while (true) {
        _Accept( ~Courier ) {
        } _Else {
            Job* job = watcardOffice.requestWork();
            unsigned int stdId = job.args.stdId;
            unsigned int fund = job.args.fund;
            WATCard* watcard = job.args.watcard;

            if ( watcard == nullptr ) {
                watcard = new WATCard();
            } // if

            bank.withdraw( stdId, fund );
            watcard.deposit( fund );
            if ( mprng( 5 ) == 0 ) {    // lost
                job.exception( new Lost );
            } else {        // deposit success
                job.delivery( watcard );
            } // if
        } // _Accept
    } // while
}

#include "groupoff.h"
#include "printer.h"

using namespace std;

/*********** Groupoff ***********
    * Purpose: An office distributes giftcards to students
    * 
    * Returns: void
    * 
    * Parameters:
    *       prt         - printer
    *       numStudents - number of students
    *       sodaCost - cost of drinks
    *       groupoffDelay - delay for giftcard distribution
    * Errors: No errors
    * 
    * Globals: N/A
***************************************/
Groupoff::Groupoff( Printer & prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupoffDelay ) 
        : printer(prt), numStudents(numStudents), sodaCost(sodaCost), groupoffDelay(groupoffDelay), numGiftcards(0) {
}

Groupoff::~Groupoff() {
    while ( !fGiftcards.empty() ) {
        WATCard::FWATCard giftcard = fGiftcards.front();
        fGiftcards.pop();
        giftcard.cancel();
    } // while

    while ( !giftcards.empty() ) {
        WATCard* giftcard = giftcards.front();
        giftcards.pop();
        delete giftcard;
    } // while
}

/*********** giftCard ***********
    * Purpose: get giftcard (As Future)
    * 
    * Returns:
    *       FWATCard - Future for WATCard
    * 
    * Parameters:
    * 
    * Errors: N/A 
    * 
    * Globals: N/A
***************************************/
WATCard::FWATCard Groupoff::giftCard() {
    WATCard::FWATCard giftcard; 
    fGiftcards.push( giftcard );
    return giftcard;
}

void Groupoff::main() {
    printer.print( Printer::Groupoff, 'S' );
    while (true) {
        _Accept( ~Groupoff ) {
            break;
        } or _When( numGiftcards < numStudents ) _Accept( giftCard ) {
            numGiftcards++;
        } _Else {
            yield( groupoffDelay );
            if ( !fGiftcards.empty() ) {
                WATCard::FWATCard fGiftcard = fGiftcards.front();
                fGiftcards.pop();

                WATCard* giftcard = new WATCard();
                giftcards.push( giftcard );

                giftcard->deposit( sodaCost );
                fGiftcard.delivery( giftcard );
                printer.print( Printer::Groupoff, 'D', sodaCost );
            } else if ( numGiftcards == numStudents ) {
                break;
            }// if
        } // _Accept
    } // while
    printer.print( Printer::Groupoff, 'F' );
}

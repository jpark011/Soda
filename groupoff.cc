#include "groupoff.h"
#include "printer.h"

using namespace std;

Groupoff::Groupoff( Printer & prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupoffDelay ) 
        : printer(prt), numStudents(numStudents), sodaCost(sodaCost), groupoffDelay(groupoffDelay), numGiftcards(0) {
}

Groupoff::~Groupoff() {
    while ( !giftcards.empty() ) {
        WATCard::FWATCard giftcard = giftcards.front();
        giftcards.pop();
        giftcard.cancel();
    } // while
}

WATCard::FWATCard Groupoff::giftCard() {
    WATCard::FWATCard giftcard; 
    giftcards.push( giftcard );
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
            if ( !giftcards.empty() ) {
                WATCard::FWATCard fGiftcard = giftcards.front();
                giftcards.pop();

                WATCard* giftcard = new WATCard();
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

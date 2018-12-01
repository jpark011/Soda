#include "groupoff.h"
#include "printer.h"

using namespace std;

Groupoff::Groupoff( Printer & prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupoffDelay ) 
        : printer(prt), numStudents(numStudents), sodaCost(sodaCost), groupoffDelay(groupoffDelay), numGiftcards(0) {
}

Groupoff::~Groupoff() {
    while ( !giftcards.empty() ) {
        WATCard::FWATCard* giftcard = giftcards.front();
        giftcards.pop_front();
        delete giftcard;
    } // while
}

WATCard::FWATCard Groupoff::giftCard() {
    WATCard::FWATCard* giftcard = new WATCard::FWATCard(); 
    giftcards.push_back( giftcard );
    return giftcard;
}

void Groupoff::main() {
    while (true) {
        _Accept( ~Groupoff ) {
            break;
        } or _When( numGiftcards < numStudents ) _Accept( giftCard ) {
            numGiftcards++;
        } _Else {
            yield( groupoffDelay );
            if ( !giftcards.empty() ) {
                WATCard::FWATCard* fGiftcard = giftcards.front();
                giftcards.pop_front();

                WATCard* giftcard = new WATCard();
                giftcard.deposit( sodaCost );
                fGiftcard->delivery( giftcard );
            } else if ( numGiftcards == numStudents ) {
                break;
            }// if
        } // _Accept
    } // while
}

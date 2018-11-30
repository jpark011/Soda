#include "groupoff.h"
#include "printer.h"

using namespace std;

Groupoff::Groupoff( Printer & prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupoffDelay ) 
        : printer(prt), numStudents(numStudents), sodaCost(sodaCost), groupoffDelay(groupoffDelay), numGiftcards(0) {

}

Groupoff::~Groupoff() {
}

WATCard::FWATCard Groupoff::giftCard() {

}

void Groupoff::main() {
    while (true) {
        _Accept( giftCard ) {
            numGiftcards++;
        } or _Accept( ~Groupoff ) {

        } _Else {
            yield( groupoffDelay );
        }
    } // while
}

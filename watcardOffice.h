#ifndef __WATCARD_OFFICE_H__
#define __WATCARD_OFFICE_H__
#include <vector>
#include "watcard.h"

_Monitor Printer;
_Monitor Bank;

_Task WATCardOffice {
    struct Job { // marshalled arguments and return future
        Args args; // call arguments (YOU DEFINE “Args”)
        WATCard::FWATCard result; // return future
        Job( Args args ) : args( args ) {}
    };

    _Task Courier {
        WATCardOffice& watcardOffice;

        void main();
    public:
        Courier( WATCardOffice& watcardOffice );
    }; // communicates with bank

    Printer& printer;
    Bank & bank;
    unsigned int numCouriers;
    vector<Courier> couriers;
    void main();
public:
    _Event Lost {}; // lost WATCard
    WATCardOffice( Printer & prt, Bank & bank, unsigned int numCouriers );
    WATCard::FWATCard create( unsigned int sid, unsigned int amount );
    WATCard::FWATCard transfer( unsigned int sid, unsigned int amount, WATCard *card );
    Job* requestWork();
};

#endif

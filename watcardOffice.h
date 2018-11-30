#ifndef __WATCARD_OFFICE_H__
#define __WATCARD_OFFICE_H__
#include <vector>
#include <queue>
#include "watcard.h"

_Monitor Printer;
_Monitor Bank;

_Task WATCardOffice {
    struct Args {
        unsigned int fund;
        WATCard* watcard;
        Args( unsigned int fund, WATCard* watcard = nullptr ) : fund(fund), watcard(watcard) {}
    };
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
    vector<Courier*> couriers;
    queue<Job*> jobs;
    void main();
public:
    _Event Lost {}; // lost WATCard
    WATCardOffice( Printer & prt, Bank & bank, unsigned int numCouriers );
    ~WATCardOffice();
    WATCard::FWATCard create( unsigned int sid, unsigned int amount );
    WATCard::FWATCard transfer( unsigned int sid, unsigned int amount, WATCard *card );
    Job* requestWork();
};

#endif

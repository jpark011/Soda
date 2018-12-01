#ifndef __GROUPOFF_H__
#define __GROUPOFF_H__
#include <queue>
#include <uFuture.h>
#include "watcard.h"

_Monitor Printer;

_Task Groupoff {
    Printer& printer;
    unsigned int numStudents;
    unsigned int sodaCost;
    unsigned int groupoffDelay;
    unsigned int numGiftcards;
    std::queue<FWATCard*> giftcards;
    
    void main();
public:
    Groupoff( Printer & prt, unsigned int numStudents, 
        unsigned int sodaCost, unsigned int groupoffDelay );
    ~Groupoff();
    WATCard::FWATCard giftCard();
};

#endif

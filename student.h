#ifndef __STUDENT_H__
#define __STUDENT_H__

_Cormonitor Printer;
_Task NameServer;
_Task WATCardOffice;
_Task Groupoff;

_Task Student {
    Printer& printer;
    NameServer& nameServer;
    WATCardOffice& watcardOffice;
    Groupoff& groupoff;
    unsigned int id;
    unsigned int maxPurchases;
    
    void main();
public:
    Student( Printer & prt, NameServer & nameServer, WATCardOffice & cardOffice, 
        Groupoff & groupoff, unsigned int id, unsigned int maxPurchases );
};

#endif

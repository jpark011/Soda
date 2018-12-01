#ifndef __VENDING_MACHINE_H__
#define __VENDING_MACHINE_H__
#include <map>

_Cormonitor Printer;
_Task NameServer;
class WATCard;

_Task VendingMachine {
public:
    enum Flavours {
        Pepsi,
        Coke,
        Cola,
        McCol       // yeah
    }; // flavours of soda (YOU DEFINE)
    static const unsigned int NUM_FLAVOURS = 4;
private:
    Printer& printer;
    NameServer& nameServer;
    unsigned int id;
    unsigned int sodaCost;
    unsigned int inventories[NUM_FLAVOURS];
    bool didBuy;
    Flavours lastFlavour;

    void main();
public:  
    _Event Free {}; // free, advertisement
    _Event Funds {}; // insufficient funds
    _Event Stock {}; // out of stock for particular flavour
    VendingMachine( Printer & prt, NameServer & nameServer, unsigned int id, 
        unsigned int sodaCost );
    ~VendingMachine();
    void buy( Flavours flavour, WATCard & card );
    unsigned int* inventory();
    void restocked();
    _Nomutex unsigned int cost();
    _Nomutex unsigned int getId();
};

#endif

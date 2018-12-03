#ifndef __TRUCK_H__
#define __TRUCK_H__

_Cormonitor Printer;
_Task BottlingPlant;
_Task NameServer;
_Task VendingMachine;

_Task Truck {
    Printer& printer; 
    NameServer& nameServer; 
    BottlingPlant& plant;
    unsigned int numVendingMachines; 
    unsigned int maxStockPerFlavour;

    bool isEmpty( unsigned int cargo[] );
    void main();
public:
    Truck( Printer & prt, NameServer & nameServer, BottlingPlant & plant,
        unsigned int numVendingMachines, unsigned int maxStockPerFlavour );
};

#endif

#ifndef __TRUCK_H__
#define __TRUCK_H__

_Monitor Printer;
_Task BottlingPlant;

_Task Truck {
    Printer& printer; 
    NameServer& nameServer; 
    BottlingPlant& plant;
    unsigned int numVendingMachines; 
    unsigned int maxStockPerFlavour;

    void main();
public:
    Truck( Printer & prt, NameServer & nameServer, BottlingPlant & plant,
        unsigned int numVendingMachines, unsigned int maxStockPerFlavour );
};

#endif

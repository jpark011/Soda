#ifndef __BOTTLING_PLANT_H__
#define __BOTTLING_PLANT_H__

_Monitor Printer;
_Task BottlingPlant;

_Task Truck {
    Printer& printer; 
    NameServer& nameServer; 
    BottlingPlant& plant;
    unsigned int numVendingMachines; 
    unsigned int maxStockPerFlavour;

    bool isEmpty();   
    void main();
public:
    Truck( Printer & prt, NameServer & nameServer, BottlingPlant & plant,
        unsigned int numVendingMachines, unsigned int maxStockPerFlavour );
};

#endif

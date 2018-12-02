#ifndef __BOTTLING_PLANT_H__
#define __BOTTLING_PLANT_H__

_Cormonitor Printer;
_Task NameServer;

_Task BottlingPlant {
    Printer& printer;
    NameServer& nameServer;
    unsigned int numVendingMachines;
    unsigned int maxShippedPerFlavour;
    unsigned int maxStockPerFlavour;
    unsigned int timeBetweenShipments;
    unsigned int production[4];
    bool timeToShut;

    void main();
public:
    _Event Shutdown {}; // shutdown plant
    BottlingPlant( Printer & prt, NameServer & nameServer, unsigned int numVendingMachines,
        unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour, 
        unsigned int timeBetweenShipments );
    ~BottlingPlant();
    void getShipment( unsigned int cargo[ ] );
};

#endif

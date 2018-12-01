#ifndef __NAME_SERVER_H__
#define __NAME_SERVER_H__
#include <vector>

_Cormonitor Printer;
_Task VendingMachine;

_Task NameServer {
    Printer & printer; 
    unsigned int numVendingMachines; 
    unsigned int numStudents;
    std::vector<VendingMachine*> vms;
    std::vector<unsigned int> stdVms;
    unsigned int lastStdId;
    
    void main();
public:
    NameServer( Printer & prt, unsigned int numVendingMachines, unsigned int numStudents );
    ~NameServer();
    void VMregister( VendingMachine *vendingmachine );
    VendingMachine* getMachine( unsigned int id );
    VendingMachine** getMachineList();
};

#endif

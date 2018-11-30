#ifndef __NAME_SERVER_H__
#define __NAME_SERVER_H__

_Monitor Printer;
_Task VendingMachine;

_Task NameServer {
    void main();
public:
    NameServer( Printer & prt, unsigned int numVendingMachines, unsigned int numStudents );
    void VMregister( VendingMachine *vendingmachine );
    VendingMachine* getMachine( unsigned int id );
    VendingMachine** getMachineList();
};

#endif

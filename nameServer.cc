#include "nameServer.h"
#include "printer.h"

using namespace std;

NameServer::NameServer( Printer & prt, unsigned int numVendingMachines, unsigned int numStudents )
        : printer(prt), numVendingMachines(numVendingMachines), numStudents(numStudents) {
    for ( unsigned int i = 0; i < numStudents; i++ ) {
        stdVms.push_back(i);
    } // for
}

void NameServer::VMregister( VendingMachine *vendingmachine ) {
    vms.push_back(vendingMachine);
}

VendingMachine* NameServer::getMachine( unsigned int id ) {
    VendingMachine* vm = vms[ stdVms[id] ];
    stdVms[id]++;
    stdVms[id] %= numVendingMachines;
    return vm; 
}

VendingMachine** NameServer::getMachineList() {
    return &vms.front();
}

void NameServer::main() {

}

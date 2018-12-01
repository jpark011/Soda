#include "nameServer.h"
#include "printer.h"

using namespace std;

NameServer::NameServer( Printer & prt, unsigned int numVendingMachines, unsigned int numStudents )
        : printer(prt), numVendingMachines(numVendingMachines), numStudents(numStudents) {
    for ( unsigned int i = 0; i < numStudents; i++ ) {
        stdVms.push_back(i % numVendingMachines);
    } // for
}

NameServer::~NameServer() {

}

void NameServer::VMregister( VendingMachine *vendingmachine ) {
    vms.push_back(vendingMachine);
}

VendingMachine* NameServer::getMachine( unsigned int id ) {
    VendingMachine* vm = vms[ stdVms[id] ];
    return vm; 
}

VendingMachine** NameServer::getMachineList() {
    return &vms.front();
}

void NameServer::main() {
    while (true) {
        _Accept( ~NameServer ) {
            break;
        } or _When( vms.size() < numVendingMachines ) _Accept( VMregister ) {
        } or _Accept( getMachine ) {
            stdVms[id]++;
            stdVms[id] %= numVendingMachines;
        } or _Accept( getMachineList ) {
        } // _Accept
    } // while
}

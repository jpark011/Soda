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
    vms.push_back( vendingmachine );
}

VendingMachine* NameServer::getMachine( unsigned int id ) {
    VendingMachine* vm = vms[ stdVms[id] ];
    lastStdId = id;
    return vm; 
}

VendingMachine** NameServer::getMachineList() {
    return &vms.front();
}

void NameServer::main() {
    printer.print( Printer::NameServer, 'S' );
    while (true) {
        _Accept( ~NameServer ) {
            break;
        } or _When( vms.size() < numVendingMachines ) _Accept( VMregister ) {
            printer.print( Printer::NameServer, 'R', vms.size()-1 );
        } or _Accept( getMachine ) {
            printer.print( Printer::NameServer, 'N', lastStdId, stdVms[lastStdId] );
            stdVms[lastStdId]++;
            stdVms[lastStdId] %= numVendingMachines;
        } or _Accept( getMachineList ) {
        } // _Accept
    } // while
    printer.print( Printer::NameServer, 'F' );
}

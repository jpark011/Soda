#include "nameServer.h"
#include "printer.h"

using namespace std;

/*********** NameServer ***********
    * Purpose: A server that locates VendingMachines
    * 
    * Returns: void
    * 
    * Parameters:
    *       prt         - printer
    *       numVendingMachine - number of vending machines
    *       numStudents - number of students
    * 
    * Errors: No errors
    * 
    * Globals: N/A
***************************************/
NameServer::NameServer( Printer & prt, unsigned int numVendingMachines, unsigned int numStudents )
        : printer(prt), numVendingMachines(numVendingMachines), numStudents(numStudents) {
    for ( unsigned int i = 0; i < numStudents; i++ ) {
        stdVms.push_back(i % numVendingMachines);
    } // for
}

NameServer::~NameServer() {

}

/*********** VMregister ***********
    * Purpose: register VendingMachine
    * 
    * Returns: void
    * 
    * Parameters:
    *       vendingmachine - vm to register
    * 
    * Errors: N/A 
    * 
    * Globals: N/A
***************************************/
void NameServer::VMregister( VendingMachine *vendingmachine ) {
    vms.push_back( vendingmachine );
}

/*********** getMachine ***********
    * Purpose: gives location of vending machine
    * 
    * Returns:
    *       VendingMachine* - vm
    * 
    * Parameters:
    *       id - vm id
    * 
    * Errors: N/A 
    * 
    * Globals: N/A
***************************************/
VendingMachine* NameServer::getMachine( unsigned int id ) {
    VendingMachine* vm = vms[ stdVms[id] ];
    lastStdId = id;
    return vm; 
}

/*********** getMachineList ***********
    * Purpose: gives location of all vending machines
    * 
    * Returns:
    *       VendingMachine** - list of vms
    * 
    * Parameters: N/A
    * 
    * Errors: N/A 
    * 
    * Globals: N/A
***************************************/
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

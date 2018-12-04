#include "parent.h"
#include "printer.h"
#include "bank.h"
#include "MPRNG.h"

using namespace std;

extern MPRNG mprng;

/*********** Parent ***********
    * Purpose: A task that puts money to students
    * 
    * Returns: void
    * 
    * Parameters:
    *       prt         - printer
    *       bank - bank
    *       numStudents - number of students
    *       parentDelay - delay between money sent
    * 
    * Errors: No errors
    * 
    * Globals: N/A
***************************************/
Parent::Parent( Printer & prt, Bank & bank, unsigned int numStudents, unsigned int parentalDelay )
        : printer(prt), bank(bank), numStudents(numStudents), parentalDelay(parentalDelay) {

}

Parent::~Parent() {

}

void Parent::main() {
    printer.print( Printer::Parent, 'S' );
    while (true) {
        _Accept( ~Parent ) {
            break;
        } _Else {
            unsigned int money = mprng(1, 3);
            unsigned int student = mprng( numStudents - 1 );

            yield( parentalDelay );

            bank.deposit( student, money );
            printer.print( Printer::Parent, 'D', student, money );
        } // _Accept
    } // while
    printer.print( Printer::Parent, 'F' );
}

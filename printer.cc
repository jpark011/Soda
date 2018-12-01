#include "printer.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <map>
#include <climits>

using namespace std;

/*********** Printer ***********
    * Purpose: A thread-safe printer to print status/progress
    *       of tour tally votes by keeping stream of each voter
    * 
    * Returns: void
    * 
    * Parameters:
    *       voters - # of voters
    * 
    * Errors: No errors
    * 
    * Globals: 
    *       buffers - vector of ostringstream
***************************************/
Printer::Printer(unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers) 
    : numStudents(numStudents), numVendingMachines(numVendingMachines), numCouriers(numCouriers) {
    resume();
}

/*********** ~Printer ***********
    * Purpose: prints out necessary msg before destructing
***************************************/
Printer::~Printer() {
    for ( unsigned int i = 0; i < buffers.size(); i++ ) {
        if ( buffers[i].tellp() != 0 ) {
            printLn();
            break;
        } // if
    } // for
    cout << "*****************" << endl;
}

/*********** printLn ***********
    * Purpose: Prints whole line by iterating each voter
***************************************/
void Printer::printLn() {
    for ( unsigned int i = 0; i < buffers.size(); i++ ) {
        cout << left << setw(8) << buffers[i].str();
        buffers[i].str("");
    } // for
    cout << endl;
}

/*********** print ***********
    * Purpose: Svaes given input into the stream and print whole line
    *       if necessary
    * 
    * Parameters:
    *       id - id of voter
    *       state - state of voter
    *       tour, ballot, numBlocked - necessary info for voter's state
***************************************/
void Printer::print( Kind kind, char state ) {
    print( kind, UINT_MAX, state );
}

void Printer::print( Kind kind, char state, int value1 ) {
    print( kind, UINT_MAX, state, value1 );
}

void Printer::print( Kind kind, char state, int value1, int value2 ) {
    print( kind, UINT_MAX, state, value1, value2 );
}

void Printer::print( Kind kind, unsigned int lid, char state ) {
    print( kind, lid, state, INT_MIN );
}

void Printer::print( Kind kind, unsigned int lid, char state, int value1 ) {
    print( kind, lid, state, value1, INT_MIN );
}

void Printer::print( Kind kind, unsigned int lid, char state, int value1, int value2 ) {
    this->kind = kind;
    this->state = state;
    this->value1 = value1;
    this->value2 = value2;
    this->lid = lid;
    resume();
}

void Printer::main() {
    map<Printer::Kind, string> kindMap;
    kindMap.emplace(Printer::Parent, "Parent");
    kindMap.emplace(Printer::Groupoff, "Gropoff");
    kindMap.emplace(Printer::WATCardOffice, "WATOff");
    kindMap.emplace(Printer::NameServer, "Names");
    kindMap.emplace(Printer::Truck, "Truck");
    kindMap.emplace(Printer::BottlingPlant, "Plant");
    kindMap.emplace(Printer::Student, "Stud");
    kindMap.emplace(Printer::Vending, "Mach");
    kindMap.emplace(Printer::Courier, "Cour");
    const unsigned int stdBegin = NUM_KINDS;
    const unsigned int vmBegin = stdBegin + numStudents;
    const unsigned int courBegin = vmBegin + numVendingMachines;

    for ( unsigned int i = 0; i < NUM_KINDS; i++ ) {
        buffers.push_back( ostringstream() );
        buffers[i] << kindMap[(Printer::Kind)i];
    } // for
    for ( unsigned int i = 0; i < numStudents; i++ ) {
        buffers.push_back( ostringstream() );
        buffers[stdBegin+i] << kindMap[Printer::Student] << i;
    } // for
    for ( unsigned int i = 0; i < numVendingMachines; i++ ) {
        buffers.push_back( ostringstream() );
        buffers[vmBegin+i] << kindMap[Printer::Vending] << i;
    } // for
    for ( unsigned int i = 0; i < numCouriers; i++ ) {
        buffers.push_back( ostringstream() );
        buffers[courBegin+i] << kindMap[Printer::Courier] << i;
    } // for
    printLn();
    for ( unsigned int i = 0; i < buffers.size(); i++ ) {
        buffers[i] << "*******";
    } // for
    printLn();

    suspend();          // INIT DONE

    while (true) {
        unsigned int i;
        switch ( kind ) {
            case Student:
                i = stdBegin + lid;
                break;
            case Vending:
                i = vmBegin + lid;
                break;
            case Courier:
                i = courBegin + lid;
                break;
            default:
                i = kind;
        }

         if ( buffers[i].tellp() != 0 ) {
            printLn();
        } // if
        buffers[i] << state;
        if ( value1 != INT_MIN )
            buffers[i]  << value1;
        if ( value2 != INT_MIN )
            buffers[i] << ','  << value2;
        suspend();
    } // while
}
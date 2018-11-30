#include "printer.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <map>

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
    static map<Printer::Kind, string> kindMap;
    kindMap.emplace(Printer::Parent, "Parent");
    kindMap.emplace(Printer::Groupoff, "Gropoff");
    kindMap.emplace(Printer::WATCardOffice, "WATOff");
    kindMap.emplace(Printer::NameServer, "Names");
    kindMap.emplace(Printer::Truck, "Truck");
    kindMap.emplace(Printer::BottlingPlant, "Plant");
    kindMap.emplace(Printer::Student, "Stud");
    kindMap.emplace(Printer::Vending, "Mach");
    kindMap.emplace(Printer::Courier, "Cour");

    unsigned int i;
    for ( i = Printer::Parent; i != Printer::Student; i++ ) {
        buffers.push_back( ostringstream() );
        buffers[i] << kindMap[(Printer::Kind)i];
    } // for
    for ( unsigned int j = 0; j < numStudents; j++ ) {
        buffers.push_back( ostringstream() );
        buffers[i+j] << kindMap[Printer::Student] << j;
    } // for
    i += numStudents;
    for ( unsigned int j = 0; j < numVendingMachines; j++ ) {
        buffers.push_back( ostringstream() );
        buffers[i+j] << kindMap[Printer::Vending] << j;
    } // for
    i += numVendingMachines;
    for ( unsigned int j = 0; j < numCouriers; j++ ) {
        buffers.push_back( ostringstream() );
        buffers[i+j] << kindMap[Printer::Courier] << j;
    } // for
    printLn();
    for ( unsigned int i = 0; i < buffers.size(); i++ ) {
        buffers[i] << "*******";
    } // for
    printLn();
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

}

void Printer::print( Kind kind, char state, int value1 ) {

}

void Printer::print( Kind kind, char state, int value1, int value2 ) {

}

void Printer::print( Kind kind, unsigned int lid, char state ) {

}

void Printer::print( Kind kind, unsigned int lid, char state, int value1 ) {

}

void Printer::print( Kind kind, unsigned int lid, char state, int value1, int value2 ) {

}


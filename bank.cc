#include "bank.h"

using namespace std;

Bank::Bank( unsigned int numStudents ) : numStudents(numStudents) {
    for ( unsigned int i = 0; i < numStudents; i++ ) {
        stdBalances.push_back(0);
    } // for
}

void Bank::deposit( unsigned int id, unsigned int amount ) {
    stdBalances[id] += amount;
}

void Bank::withdraw( unsigned int id, unsigned int amount ) {
    while ( stdBalances[id] < amount ) 
        _Accept( deposit );
    stdBalances[id] -= amount;
}

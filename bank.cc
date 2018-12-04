#include "bank.h"

using namespace std;

/*********** Bank ***********
    * Purpose: A class that transacts money
    * 
    * Returns: void
    * 
    * Parameters:
    *       numStudents - number of students
    * 
    * Errors: No errors
    * 
    * Globals: N/A
***************************************/
Bank::Bank( unsigned int numStudents ) : numStudents(numStudents) {
    for ( unsigned int i = 0; i < numStudents; i++ ) {
        stdBalances.push_back(0);
    } // for
}

/*********** deposit ***********
    * Purpose: Add money
    * 
    * Returns: void
    * 
    * Parameters:
    *       id - student id
    *       amount - money value
    * 
    * Errors: No errors
    * 
    * Globals: N/A
***************************************/
void Bank::deposit( unsigned int id, unsigned int amount ) {
    stdBalances[id] += amount;
}

/*********** withdraw ***********
    * Purpose: Remove money
    * 
    * Returns: void
    * 
    * Parameters:
    *       id - student id
    *       amount - money value
    * 
    * Errors: No errors
    * 
    * Globals: N/A
***************************************/
void Bank::withdraw( unsigned int id, unsigned int amount ) {
    while ( stdBalances[id] < amount ) 
        _Accept( deposit );
    stdBalances[id] -= amount;
}

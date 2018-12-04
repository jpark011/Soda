#include "watcard.h"

using namespace std;

/*********** WATCard ***********
    * Purpose: A card with balance
    * 
    * Returns: void
    * 
    * Parameters: N/A
    * 
    * Errors: No errors
    * 
    * Globals: N/A
***************************************/
WATCard::WATCard() : balance(0) {
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
void WATCard::deposit( unsigned int amount ) {
    balance += amount;
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
void WATCard::withdraw( unsigned int amount ) {
    balance -= amount;
}

/*********** getBalance ***********
    * Purpose: check balance
    * 
    * Returns: balance
    * 
    * Parameters:
    * 
    * Errors: No errors
    * 
    * Globals: N/A
***************************************/
unsigned int WATCard::getBalance() {
    return balance;
}

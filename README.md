# Soda
On campus vending machine system simulator using uC++

## Architecture
### Administrator
  1. __BottlingPlant__ : Manage _Truck_ tasks and deliver bottles.
  2. __CardOffice__ : Manage _Student_ and _VendingMachine_ tasks and act as an mediator between the bank.
  3. __NameServer__ : Manage _VendingMachine_ (their location)
  
### Worker
 1. __Truck__ : Frequently delivers from the plant to vending mahines.
 2. __Student__ : Frequently buys bottles from vending machines.
 

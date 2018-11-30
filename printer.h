#ifndef __PRINTER_H__
#define __PRINTER_H__
#include <sstream>
#include <vector>

_Monitor Printer {    // chose one of the two kinds of type constructor
    unsigned int numStudents; 
    unsigned int numVendingMachines; 
    unsigned int numCouriers; 
    std::vector<std::ostringstream> buffers;

    void printLn();
  public:
    enum Kind { 
        Parent,
        Groupoff,
        WATCardOffice,
        NameServer,
        Truck,
        BottlingPlant,
        Student,
        Vending,
        Courier
     };
    Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers );
    ~Printer();
    void print( Kind kind, char state );
    void print( Kind kind, char state, int value1 );
    void print( Kind kind, char state, int value1, int value2 );
    void print( Kind kind, unsigned int lid, char state );
    void print( Kind kind, unsigned int lid, char state, int value1 );
    void print( Kind kind, unsigned int lid, char state, int value1, int value2 );
};

#endif

#ifndef __PRINTER_H__
#define __PRINTER_H__
#include <sstream>
#include <vector>

_Cormonitor Printer {    // chose one of the two kinds of type constructor
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
private:
    static const unsigned int NUM_KINDS = 6;
    unsigned int numStudents; 
    unsigned int numVendingMachines; 
    unsigned int numCouriers; 
    std::vector<std::ostringstream> buffers;

    Kind kind;
    char state;
    int value1;
    int value2;
    unsigned int lid;

    void printLn();
    void main();
  public:
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

#ifndef __PARENT_H__
#define __PARENT_H__

_Cormonitor Printer;
_Monitor Bank;

_Task Parent {
    Printer& printer;
    Bank& bank;
    unsigned int numStudents;
    unsigned int parentalDelay;

    void main();
public:
    Parent( Printer & prt, Bank & bank, unsigned int numStudents, 
        unsigned int parentalDelay );
    ~Parent();
};

#endif

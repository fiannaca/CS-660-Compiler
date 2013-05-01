/**
 * SpillTest.cpp
 *
 * This file tests register allocation and register spilling.
 */

#include <iostream>
#include <sstream>
#include <fstream>

#include "RegAllocTable.h"
#include "AddressTable.h"

using namespace std;

int main()
{
    AddressTable addtab;
    RegAllocTable regtab(8, "$t", &addtab);
    
    fstream fout;
    fout.open("spill_test.out", std::ios_base::out);
    regtab.SetFstream(&fout);
    
    bool isNew = false;
    
    //Request 12 registers
    for( int i = 0; i < 12; i++)
    {
        stringstream ss;
        ss << "I" << (i + 1);
        string reg = regtab.GetRegister(ss.str(), isNew);
        cout << "Register " << reg << " allocated for " << ss.str() 
             << ", isNew: " << isNew << endl;
    }
    
    regtab.PrintRegisters();
    
    //Release one of the temps in a spill
    cout << "Releasing a spill register: I4" << endl;    
    regtab.FreeRegister("I4");    
    regtab.PrintRegisters();
    
    //Release one of the temps in a real register
    cout << "Releasing a real register: I5" << endl;    
    regtab.FreeRegister("I5");    
    regtab.PrintRegisters();
    
    //Get a register for one of the temps that is already in a spill
    cout << "Swapping a spill register back into a real register: I3" << endl;    
    string reg = regtab.GetRegister("I3", isNew);
    regtab.PrintRegisters();
    
    //Get a register for one of the temps that is already in a real register
    cout << "Getting a register for a temp already in a register: I7" << endl;
    reg = regtab.GetRegister("I7", isNew);
    regtab.PrintRegisters();
    
    fout.close();
}

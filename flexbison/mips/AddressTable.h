#ifndef ADDRESSTABLE_H
#define ADDRESSTABLE_H

#include <string>
#include <map>

using namespace std;

enum MemLocation {
    MEMORY,
    REGISTER,
    BOTH
};

struct Address {
    string      varName;
    MemLocation loc;
    string      reg;
    int         memOffset;
    
    Address()
    {
        varName = "";
        loc = MEMORY;
        regNum = -1;
        memOffset = -1;
    }
    
    Address(const Address& rhs)
    {
        varName = rhs.varName;
        loc = rhs.loc;
        regNum = rhs.regNum;
        memOffset = rhs.memOffset;
    }
};

class AddressTable {
    public:
        AddressTable();
        ~AddressTable();
        
        void Add(string name, string reg);
        void Add(string name, int offset);
        void Add(string name, string reg, int offset);
        
        void Remove(string name);
        
        Address* GetAddress(string name);        
        
        void clear();
        int  size();
        
    private:
        map<string, Address*> Variables;
};

#endif // ! ADDRESSTABLE_H

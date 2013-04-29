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
    int         regNum;
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
        
        void AddReg(string name, int regNum);
        void AddMem(string name, int offset);
        void Add(string name, int regNum, int offset);
        
        void Remove(string name);
        
        Address* GetAddress(string name);        
        
        void clear();
        int  size();
        
    private:
        map<string, Address*> Variables;
};

#endif // ! ADDRESSTABLE_H

#include "AddressTable.h"

AddressTable::AddressTable()
{

}

AddressTable::~AddressTable()
{

}

void AddressTable::AddReg(string name, int rname)
{
    Address* newAddr = new Address;
    
    newAddr->varName = name;
    newAddr->regNum = rname;
    newAddr->loc = REGISTER;
    
    Variables[name] = newAddr;
}

void AddressTable::AddMem(string name, int offset)
{
    Address* newAddr = new Address;
    
    newAddr->varName = name;
    newAddr->memOffset = offset;
    newAddr->loc = MEMORY;
    
    Variables[name] = newAddr;
}

void AddressTable::Add(string name, int rname, int offset)
{
    Address* newAddr = new Address;
    
    newAddr->varName = name;
    newAddr->regNum = rname;
    newAddr->memOffset = offset;
    newAddr->loc = BOTH;
    
    Variables[name] = newAddr;
}

void AddressTable::Remove(string name)
{
    Variables.erase(name);
}

Address* AddressTable::GetAddress(string name)
{
    return Variables[name];
}

void AddressTable::clear()
{
    Variables.clear();
}

int  AddressTable::size()
{
    return Variables.size();
}

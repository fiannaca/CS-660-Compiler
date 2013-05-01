#include "AddressTable.h"

AddressTable::AddressTable()
{

}

AddressTable::~AddressTable()
{

}

void AddressTable::AddReg(string name, string rname)
{
    Address* newAddr = new Address;
    
    newAddr->varName = name;
    newAddr->reg = rname;
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

void AddressTable::Add(string name, string rname, int offset)
{
    Address* newAddr = new Address;
    
    newAddr->varName = name;
    newAddr->reg = rname;
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

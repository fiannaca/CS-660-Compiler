#include "RegAllocTable.h"

RegAllocTable::RegAllocTable(int maxRegisters, string regPrefix, AddressTable* at)
    : numSpills(20)
{
    size = maxRegisters;
    prefix = regPrefix;
    addtab = at;
    
    registers = new Register[size];
    spills = new Register[numSpills];
    
    for(int i = 0; i < size; ++i)
    {
        stringstream ss;
        
        ss << prefix << i;
        
        registers[i].name = ss.str();
    }
    
    //Initialize the spill registers
    for(int i = 0; i < numSpills; ++i)
    {
        registers[i].name = "spill";
        registers[i].spillOffset = i * 4;
    }
}

RegAllocTable::~RegAllocTable()
{
    delete [] registers;
}

std::string RegAllocTable::GetRegister(std::string name, bool &isNew)
{
    int ctr = 0;
    bool found = false;
    string regName = "";
    
    //See if the name is already in a register
    for(int i = 0; i < size; ++i)
    {
        if(registers[i].isOwned && registers[i].owner == name)
        {
            isNew = false;
            incrementLifes();
            return registers[i].name;
        }
    }
    
    //See if the name is in a spill register
    
        //Switch it out to a real register
    
    //Search for an open register
    while(ctr < size && !found)
    {
        found = !registers[ctr].isOwned;
        
        if(!found)
            ++ctr;
    }
    
    if(!found)
    {
        //Spilling needs to occur
        
    }
    else
    {
        //There is an open register
        registers[ctr].isOwned = true;
        registers[ctr].owner = name;
        regName = registers[ctr].name;
    }
    
    isNew = true;
    incrementLifes();
    return regName;
}

void RegAllocTable::FreeRegister(std::string name)
{
    int ctr = 0;
    
    while(ctr < size)
    {
        if(registers[ctr].owner == name)
        {
            registers[ctr].isOwned = false;
            registers[ctr].owner = "";
            registers[ctr].lifespan = 0;
            
            return;
        }
        else
        {
            ++ctr;
        }        
    }
    
    //If there are spilled registers then one should be moved into this one
}

int RegAllocTable::GetSpillSize()
{
    return (numSpills * 4);
}

void RegAllocTable::incrementLifes()
{
    for(int i = 0; i < size; ++i)
    {
        if(registers[i].isOwned)
            registers[i].lifespan++;
    }
}

























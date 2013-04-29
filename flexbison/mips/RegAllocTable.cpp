#include "RegAllocTable.h"

RegAllocTable::RegAllocTable(int maxRegisters, string regPrefix, AddressTable* at)
    : numSpills(20)
    , width(8)
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
        spills[i].name = "spill";
        spills[i].spillOffset = i * 4;
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
    
    //See if the name is already in a spill register
    for(int i = 0; i < numSpills; ++i)
    {
        if(spills[i].isOwned && spills[i].owner == name)
        {
            //Switch it out to a real register
            int reg = GetHighestLifeIndex();
            SwapRegToSpill(reg, i);
            
            isNew = true;
            incrementLifes();
            
            return registers[reg].name;
        }
    }
    
    //Search for an open register
    ctr = GetOpenRegIndex(found);
    
    if(!found)
    {
        //Spilling needs to occur
        ctr = GetHighestLifeIndex();
        RegToSpill(ctr, GetSpillIndex());
    }
    
    registers[ctr].isOwned = true;
    registers[ctr].owner = name;
    regName = registers[ctr].name;
        
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
    for(int i = 0; i < numSpills; ++i)
    {
        //Just choose the first spill to be moved back
        if(spills[i].isOwned)
        {
            SpillToReg(i, ctr);
            return;
        }
    }
}

int RegAllocTable::GetSpillSize()
{
    return (numSpills * 4);
}

void RegAllocTable::SetFstream(fstream *fs)
{
    fout = fs;
}

int RegAllocTable::GetSpillIndex()
{
    for(int i = 0; i < numSpills; ++i)
    {
        if(!spills[i].isOwned)
            return i;
    }
}

int RegAllocTable::GetOpenRegIndex(bool &found)
{
    int ctr = 0;
    found = false;
    
    while(ctr < size && !found)
    {
        found = !registers[ctr].isOwned;
        
        if(!found)
            ++ctr;
    }
    
    return ctr;
}

int RegAllocTable::GetHighestLifeIndex()
{
    int max = 0;
    
    for(int i = 0; i < size; ++i)
    {
        if(registers[i].lifespan > max)
            max = registers[i].lifespan;
    }
    
    return max;
}

void RegAllocTable::incrementLifes()
{
    for(int i = 0; i < size; ++i)
    {
        if(registers[i].isOwned)
            registers[i].lifespan++;
    }
    
    for(int i = 0; i < numSpills; ++i)
    {
        if(spills[i].isOwned)
            spills[i].lifespan++;
    }
}

void RegAllocTable::RegToSpill(int rindex, int sindex)
{
    //Output MIPS
    (*fout) << "\tsw" << registers[rindex].name << ", " 
            << "spills + " << spills[sindex].spillOffset << endl;
         
    //Update the Spill register information
    spills[sindex].lifespan = 0;
    spills[sindex].isOwned = true;
    spills[sindex].owner = registers[rindex].owner;
    
    //Update the real register information
    registers[rindex].lifespan = 0;
    registers[rindex].isOwned = false;
    registers[rindex].owner = "";
}

void RegAllocTable::SpillToReg(int sindex, int rindex)
{
    //Output MIPS
    (*fout) << "\tlw" << registers[rindex].name << ", " 
            << "spills + " << spills[sindex].spillOffset << endl << endl;
    
    //Update the real register information
    registers[rindex].lifespan = 0;
    registers[rindex].isOwned = true;
    registers[rindex].owner = spills[sindex].owner;
    
    //Update the Spill register information
    spills[sindex].lifespan = 0;
    spills[sindex].isOwned = false;
    spills[sindex].owner = "";
    
    
}

void RegAllocTable::SwapRegToSpill(int rindex, int sindex)
{
    //Output MIPS
	(*fout) << "\tmove $t8, " << registers[rindex].name << endl
	        << "\tlw " << registers[rindex].name 
	        << ", spills + " << spills[sindex].spillOffset << endl
	        << "\tsw $t8, spills + " << spills[sindex].spillOffset << endl << endl;
	     
    //Update the real register information
    string tmp = registers[rindex].owner;
    
    registers[rindex].lifespan = 0;
    registers[rindex].isOwned = true;
    registers[rindex].owner = spills[sindex].owner;
    
    //Update the Spill register information
    spills[sindex].lifespan = 0;
    spills[sindex].isOwned = true;
    spills[sindex].owner = tmp;
}























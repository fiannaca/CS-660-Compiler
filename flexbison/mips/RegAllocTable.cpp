#include "RegAllocTable.h"

RegAllocTable::RegAllocTable(int maxRegisters, string regPrefix)
    : numSpills(20)
    , width(8)
    , UpdatedEvent(this)
    , verbose(false)
{
    size = maxRegisters;
    prefix = regPrefix;
    
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

void RegAllocTable::PrintRegisters()
{
    cout << endl << "Registers:" << endl;
    
    for(int i = 0; i < size; i++)
    {
        if(registers[i].isOwned)
            cout << i << ". Name: " << registers[i].name 
                 << ", Owner: " << registers[i].owner << endl;
    }
    
    cout << endl << "Spill Registers:" << endl;
    
    for(int i = 0; i < numSpills; i++)
    {
        if(spills[i].isOwned)
            cout << i << ". Name: " << spills[i].name 
                 << ", Offset: " << spills[i].spillOffset 
                 << ", Owner: " << spills[i].owner << endl;
    }
    
    cout << endl;
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
    
    UpdatedEvent.FireEvent(NULL);
    
    return regName;
}

void RegAllocTable::FreeRegister(std::string name)
{
    int ctr = 0;
    bool found = false;
    
    while(ctr < size && !found)
    {
        if(registers[ctr].owner == name)
        {
        	if(verbose)
        		(*fout) << "\t# Freeing register " << registers[ctr].name << endl;
        		
            registers[ctr].isOwned = false;
            registers[ctr].owner = "";
            registers[ctr].lifespan = 0;
            
            found = true;
        }
        else
        {
            ++ctr;
        }        
    }
    
    //Check if it is in a spill register if it wasn't found in the regular registers
    if(!found)
    {
        ctr = 0;
        while(ctr < numSpills)
        {
            if(spills[ctr].owner == name)
            {
            	if(verbose)
            	{
		    		(*fout) << "\t# Freeing spill register " << ctr 
		    				<< " (" << spills[ctr].name 
		    				<< " + " << spills[ctr].spillOffset << ")"
		    				<< endl;
        		}
        		
                spills[ctr].isOwned = false;
                spills[ctr].owner = "";
                spills[ctr].lifespan = 0;
                
                UpdatedEvent.FireEvent(NULL);
                
                return; //return since no spills need to move to spills
            }
            else
            {
                ++ctr;
            }        
        }
    }
    
    if(found)
    {
        //If there are spilled registers then one should be moved into this one
        for(int i = 0; i < numSpills; ++i)
        {
            //Just choose the first spill to be moved back
            if(spills[i].isOwned)
            {
            	if(verbose)
            	{
		        	(*fout) << "\t# Restoring spill register " << i 
		    				<< " (" << spills[i].name 
		    				<< " + " << spills[i].spillOffset << ")"
		    				<< " to the real register " << registers[ctr].name
		    				<< endl;
        		}
        			
                SpillToReg(i, ctr);
                UpdatedEvent.FireEvent(NULL);
                return;
            }
        }
    }
}

int RegAllocTable::GetSpillSize()
{
    return (numSpills * 4);
}

string RegAllocTable::Lookup(string name)
{
	for(int i = 0; i < size; ++i)
	{
		if(registers[i].isOwned && registers[i].owner == name)
			return registers[i].name;
	}
	
	for(int i = 0; i < numSpills; ++i)
	{
		if(spills[i].isOwned && spills[i].owner == name)
			return spills[i].name;
	}
	
	return "";
}

string RegAllocTable::LookupOwner(string reg)
{
	for(int i = 0; i < size; ++i)
	{
		if(registers[i].name == reg)
			return registers[i].owner;
	}
}

void RegAllocTable::SetFstream(fstream *fs)
{
    fout = fs;
}

void RegAllocTable::SetVerbose(bool flag)
{
	verbose = flag;
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
    int index = 0;
    
    for(int i = 0; i < size; ++i)
    {
        if(registers[i].lifespan > max)
        {
            max = registers[i].lifespan;
            index = i;
        }
    }
    
    return index;
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
	if(verbose)
	{
		(*fout) << "\t# Storing the real register " << registers[rindex].name
		   		<< " into the spill register " << spills[sindex].spillOffset
		   		<< endl;
    }
    
    //Output MIPS
    (*fout) << "\tsw \t" << registers[rindex].name << ", " 
            << "spills + " << spills[sindex].spillOffset << endl << endl;
         
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
    (*fout) << "\tlw \t" << registers[rindex].name << ", " 
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
	if(verbose)
	{
		(*fout) << "\t# Swapping spill register at offset " << spills[sindex].spillOffset
			   	<< " with the real register " << registers[rindex].name
			   	<< endl;
    }
       
    //Output MIPS
	(*fout) << "\tmove \t$t8, " << registers[rindex].name << endl
	        << "\tlw \t" << registers[rindex].name 
	        << ", spills + " << spills[sindex].spillOffset << endl
	        << "\tsw \t$t8, spills + " << spills[sindex].spillOffset << endl << endl;
	     
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























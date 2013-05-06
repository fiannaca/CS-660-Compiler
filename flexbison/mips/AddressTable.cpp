#include "AddressTable.h"

AddressTable::AddressTable(RegAllocTable* rt)
{
	regtab = rt;
}

AddressTable::~AddressTable()
{
	regtab = NULL;
}

void AddressTable::Add(string name, string rname)
{
    Address* newAddr = new Address;
    
    newAddr->varName = name;
    newAddr->reg = rname;
    newAddr->loc = REGISTER;
    
    Variables[name] = newAddr;
}

void AddressTable::Add(string name, int offset)
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

string AddressTable::Load(string name)
{
	auto it = Variables.find(name);
	
	if(it != Variables.end())
	{
		MemLocation loc = it->second.loc;
		if(loc == MEMORY)
		{
			//The variable is in memory and needs to be pulled in
			reg = regtab->GetRegister(name);
			
		}
		else
		{
			
		}
	}
}
   
void AddressTable::Store(string name)
{

}

void AddressTable::clear()
{
    Variables.clear();
}

int  AddressTable::size()
{
    return Variables.size();
}

void AddressTable::SetFstream(fstream* fs)
{
	fout = fs;
}

void AddressTable::Print()
{
    //Output the top of the table
	cout << endl << endl 
	     << "Address Table:" << endl 
		 << setw(80)
		 << setfill('=') << "=" << endl;
	
	//Output the headers
	cout << setfill(' ') 
	     << setw(20) << "Name" 
	     << setw(20) << "Location"
	     << setw(20) << "Register"
	     << setw(20) << "Memory Offset" << endl
	     << setfill('-') << setw(80) << "-" 
	     << setfill(' ') << endl;
	
	//Output the contents
	for(auto it = Variables.begin(); it != Variables.end(); ++it)
	{
	    switch(it->second->loc)
	    {
	        case MEMORY:
	            cout << setw(20) << it->first
	                 << setw(20) << "MEMORY"
	                 << setw(20) << " "
	                 << setw(20) << it->second->memOffset
	                 << endl;
	            break;
	            
	        case REGISTER:
	            cout << setw(20) << it->first
	                 << setw(20) << "REGISTER"
	                 << setw(20) << it->second->reg
	                 << setw(20) << " "
	                 << endl;
	            break;
	            
	        case BOTH:
	            cout << setw(20) << it->first
	                 << setw(20) << "BOTH"
	                 << setw(20) << it->second->reg
	                 << setw(20) << it->second->memOffset
	                 << endl;
	            break;
	    }
	}
	
	//Output the bottom line
	cout << setw(80)
	     << setfill('=') << "=" << endl << endl;
}















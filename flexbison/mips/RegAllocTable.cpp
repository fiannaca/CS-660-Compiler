#include "RegAllocTable.h"

RegAllocTable::RegAllocTable(int maxRegisters, string regPrefix)
{
    size = maxRegisters;
    prefix = regPrefix;
    
    for(int i = 0; i < size; ++i)
    {
        registers.push_back(Register());
    }
}

RegAllocTable::~RegAllocTable()
{

}

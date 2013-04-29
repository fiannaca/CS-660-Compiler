#ifndef REGALLOCTABLE_H
#define REGALLOCTABLE_H

#include <string>
#include <sstream>
#include <vector>

#include "AddressTable.h"

using namespace std;

struct Register {
    /**
     * Indicates how long the register has been owned for.
     */
    int    lifespan;
    
    /**
     * Indicates if the register is owned.
     */
    bool   isOwned;
    
    /**
     * Name of the temporary or variable which is loaded in the register.
     */
    string owner;
    
    /**
     * Name used by the assembly language to reference the register.
     */
    string name;
    
    /**
     *
     */
    int spillOffset;
    
    Register() {
        lifespan = 0;
        isOwned = false;
        owner = "";
        name = "";
        spillOffset = 0;
    }
    
    Register(const Register& rhs) {
        lifespan = rhs.lifespan;
        isOwned = rhs.isOwned;
        owner = rhs.owner;
        name = rhs.name;
        spillOffset = rhs.spillOffset;
    }
};

class RegAllocTable {
    public:
        RegAllocTable(int maxRegisters, string regPrefix, AddressTable* at);
        ~RegAllocTable();
        
        /**
         * Handles the allocation of registers including spilling when required.
         * This function first checks if the name is already in a register. If
         * the name is already assigned to a register, then isNew is set to false
         * and the name of the register is returned. If the name has not already
         * been assigned to a register, then the function attempts to find an
         * open register. If one is present, then the name is assigned to it, 
         * isNew is set to true, and the name of the register is returned. 
         * Otherwise, spilling must occur. This function uses a Last Recently
         * Allocated algorithm to decide which register should be spilled to 
         * memory and allocated to the new name.
         *
         * @param name The name of the temporary register in the 3AC which 
         *                 needs to be mapped to a real register.
         * @param isNew    An output ref parameter indicating if the temp register
         *                 was already mapped to this real register, or if the
         *                 mapping is new.
         * @return The name of the real register to which the temp register has
         *         been mapped/assigned.
         */
        std::string GetRegister(std::string name, bool &isNew);
        
        /**
         * Handles the deallocation of a register assigned to a temporary. Note:
         * this function DOES NOT save anything to memory! This function only 
         * marks a register as available, allowing that register to be allocated
         * again in the future.
         *
         * @param name The name of the owner of a register which must be freed
         */
        void FreeRegister(std::string name);
        
        /**
         * Returns the size of the global .space directive that needs to be 
         * allocated for the spill registers.
         */
        int GetSpillSize();
        
    private:
        int size; /** Indicates the number of available registers that can be used */
        int numSpills; /** Indicates the number of spill registers allocated by default in the data section */
        string prefix; /**< Indicates how registers are named (i.e. $t for MIPS) */
        
        void incrementLifes();
        void RegToMem(string rname, int offset);
        
        /**
         * A reference to the address table. This should never be deleted since
         * the tac2mips class is the owner of the Address Table.
         */
        AddressTable* addtab;
        
        /**
         * Collection of registers.
         */
        Register* registers;
        Register* spills;
};

#endif // ! REGALLOCTABLE_H

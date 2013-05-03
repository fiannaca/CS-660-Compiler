#ifndef REGALLOCTABLE_H
#define REGALLOCTABLE_H

#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

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
     * Indicates the offset of this register into the spill register memory segment
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
        RegAllocTable(int maxRegisters, string regPrefix);
        ~RegAllocTable();
        
        /**
         * This function is for the purpose of debugging the register allocation
         * algorithms. It simply prints out a listing of each of the owned 
         * registers.
         */
        void PrintRegisters();
        
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
        
        /**
         * Used to set the pointer to the output stream which must be created
         * by the owning class (i.e. tac2mips).
         */
        void SetFstream(fstream *fs);
        
    private:
        int size; /** Indicates the number of available registers that can be used */
        
        string prefix; /**< Indicates how registers are named (i.e. $t for MIPS) */
        
        int width; /**< Indicates the column width in the output MIPS */
        /**
         * Indicates the number of spill registers allocated by default in the 
         * data section 
         */
        int numSpills;
        
        fstream *fout; /**< A pointer to the MIPS file */
               
        /**
         * Finds the index of the next open spill register.
         */
        int GetSpillIndex();
        
        /**
         * Finds the index of the next open register.
         *
         * @param found Indicates if an open register was found.
         * @return The index of the open register. Invalid if found == false
         */
        int GetOpenRegIndex(bool &found);
        
        /**
         * Increments the lifespan of all registers (real and spill) which are 
         * owned.
         */
        void incrementLifes();
        
        /**
         * Gets the index of the register with the highest lifespan.
         * 
         * @return The index of the register with the highest lifespan.
         */
        int GetHighestLifeIndex();
        
        /**
         * Outputs the MIPS code to move the contents of a real register to a
         * spill register.
         */
        void RegToSpill(int rindex, int sindex);
        
        /**
         * Outputs the MIPS code to move the contents of a spill register into
         * a real register.
         */
        void SpillToReg(int sindex, int rindex);
        
        /**
         * Outputs the MIPS code to swap a spill register with a real register.
         */
        void SwapRegToSpill(int rindex, int sindex);
        
        /**
         * Collection of real registers.
         */
        Register* registers;
        
        /**
         * Collection of spill registers declared in the global data block.
         */
        Register* spills;
};

#endif // ! REGALLOCTABLE_H

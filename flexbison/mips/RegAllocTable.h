#ifndef REGALLOCTABLE_H
#define REGALLOCTABLE_H

#include <string>
#include <vector>

using namespace std;

struct Register {
    int   lifespan;
    bool  isOwned;
    string owner;
    string name;
    
    Register() {
        lifespan = 0;
        isOwned = false;
        owner = "";
        name = "";
    }
    
    Register(const Register& rhs) {
        lifespan = rhs.lifespan;
        isOwned = rhs.isOwned;
        owner = rhs.owner;
        name = rhs.name;
    }
};

class RegAllocTable {
    public:
        RegAllocTable(int maxRegisters, string regPrefix);
        ~RegAllocTable();
        
        /**
         * Handles the allocation of registers including spilling when required.
         *
         * @param tempName The name of the temporary register in the 3AC which 
         *                 needs to be mapped to a real register.
         * @param isNew    An output ref parameter indicating if the temp register
         *                 was already mapped to this real register, or if the
         *                 mapping is new.
         * @return The name of the real register to which the temp register has
         *         been mapped/assigned.
         */
        std::string GetRegister(std::string tempName, bool &isNew);
        
        /**
         * Handles the deallocation of a register assigned to a temporary.
         */
        void FreeRegister(std::string tempName);
        
    private:
        int size; /** Indicates the number of available registers that can be used */
        string prefix; /**< Indicates how registers are named (i.e. $t for MIPS) */
        
        /**
         * Collection of registers.
         */
        vector<Register> registers;
};

#endif // ! REGALLOCTABLE_H

#ifndef ADDRESSTABLE_H
#define ADDRESSTABLE_H

#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <map>

#include "RegAllocTable.h"

using namespace std;

/**
 * This enum describes the location of a given variable in the program, whether
 * it is in memory, in a register, or in both.
 */
enum MemLocation {
    MEMORY,
    REGISTER,
    BOTH
};

/**
 * This struct describes the entire location information of a variable in the 
 * program including the memory location flag, the name of the register it is
 * in (if it is in a register), and the memory offset location it is in (if it
 * is also in memory).
 */
struct Address {
	/**
	 * The name of the variable.
	 */
    string      varName;
    
	/**
	 * Flag indicating where the variable is (memory, register, or both).
	 */
    MemLocation loc;
    
	/**
	 * The register the variable is located in.
	 */
    string      reg;
    
	/**
	 * The memory offset of the variable.
	 */
    int         memOffset;
    
	/**
	 * Default constructor.
	 */
    Address()
    {
        varName = "";
        loc = MEMORY;
        reg = "";
        memOffset = -1;
    }
    
	/**
	 * Standard copy constructor.
	 */
    Address(const Address& rhs)
    {
        varName = rhs.varName;
        loc = rhs.loc;
        reg = rhs.reg;
        memOffset = rhs.memOffset;
    }
};

class AddressTable {
    public:
    
		/**
		 * The default constructor for the address table.
		 *
		 * @param rt A reference to the register allocation table.
		 */
        AddressTable(RegAllocTable* rt);
    
		/**
		 * Destructor for the address table.
		 */
        ~AddressTable();
        
		/**
		 * Adds a variable to the address table and sets the variable's 
		 * location to the provided register.
		 * 
		 * @param name The name of the variable.
		 * @param reg The name of the register the variable is in.
		 */
        void Add(string name, string reg);
    
		/**
		 * Adds a variable to the address table and sets the variable's 
		 * location to the provided memory offset.
		 * 
		 * @param name The name of the variable.
		 * @param offset The memory offset the variable is in.
		 */
        void Add(string name, int offset);
    
		/**
		 * Adds a variable to the address table and sets the variable's
		 * location to both the provided register and memory offset.
		 * 
		 * @param name The name of the variable.
		 * @param reg The name of the register the variable is in.
		 * @param offset The memory offset the variable is in.
		 */
        void Add(string name, string reg, int offset);
        
		/**
		 * Removes the record for the given variable from the address table. In
		 * essence, by calling this function, it is assumed that the variable 
		 * will never again be used in the program.
		 *
		 * @param name The name of the variable to remove from the table.
		 */
        void Remove(string name);
        
        /**
         * This function looks up the variable of the given name and then 
         * returns a pointer to the record for that variable. This function can
		 * also be used to determine if a string refers to a variable or a temp
		 * register. If the return value is NULL, then the string passed in refers 
		 * to a temp register since the string is not a name of a variable in the
		 * table.
         *
         * @param name The name of the variable in the table to look up.
         * @return A pointer to the address table record for the requested variable.
         */
        Address* Lookup(string name);        
        
        /**
         * This function is responsible for loading variables from memory into
         * a register.
         *
         * @param name The name of the variable to load
         * @return The name of the register the variable has been loaded into
         */
        string Load(string name);     
        
        /**
         * This function is responsible for loading variables from memory into
         * a register.
         *
         * @param addr A reference to the address struct of the variable to load
         * @return The name of the register the variable has been loaded into
         */
        string Load(Address* addr);
        
        /**
         * This function is responsible for storing the given variable back into
         * memory (no effect will occur if the provided variable is only 
         * currently in memory and not in a register).
         *
         * @param name The name of the variable to store back to memory.
         */
        void Store(string name);
        
        /**
         * This function stores the value of a register into a variable in memory.
         * In addition, this requires that if the variable was already in a register,
         * the register must be freed and the location of the variable must be 
         * set to MEMORY.
         *
         * @param reg The register to store to the variable
         * @param name The variable name to store a value to
         */
        void Store(string reg, string name);
        
        /**
         * This static function receives the event notification from the register
         * allocation table and fires the update function for the provided
         * address table context object
         *
         * @param src A reference to the register allocation table
         * @param data This will ALWAYS be a null pointer
         * @param context This is a pointer to the AddressTable object
         */
        static void Update(RegAllocTable *src, void *data, void *context);
        
        /**
         * This function is responsible for updating the register locations stored
         * in the address table for any variables currently in a register after 
         * any operations which require register changes
         *
         * @param src A reference to the register allocation table
         */
        void UpdateRegisters(RegAllocTable *src);
        
        /**
         * Clears out all the records in the address table.
         */
        void clear();
        
        /**
         * Returns the number of records in the address table.
         *
         * @return The number of records in the address table.
         */
        int  size();
		
		/**
		 * Sets the output stream.
		 *
		 * @param fs A reference to the filestream.
		 */
		void SetFstream(fstream* fs);
        
        /**
         * This function is intended for debugging uses only. This function 
         * prints out the current contents of the address table.
         */
        void Print();
        
    private:
    	/**
    	 * The internal data structure for the table.
    	 */
        map<string, Address*> Variables;
        
        /**
         * A reference to the register allocation table owned by the tac2mips 
         * object which also owns this object.
         */
        RegAllocTable* regtab;
		
		/**
		 * The output stream to print MIPS to.
		 */
		fstream *fout;
};

#endif // ! ADDRESSTABLE_H

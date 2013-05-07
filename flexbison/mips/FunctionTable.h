#ifndef FUNCTIONTABLE_H
#define FUNCTIONTABLE_H

#include <map>
#include <list>
#include <string>
#include <iostream>

using namespace std;

struct Parameter {
	string name;
	
	bool byValue;
	
	int size;
	
	bool byRegister;
	
	string regName;
	
	int offset;
};

struct Function {
	/**
	 * The name of the function
	 */
	string name;
	
	/**
	 * Indicates if the function has a return value;
	 */
	bool hasReturn;
	
	/**
	 * The variables in the function for which stack space must be allocated
	 * (The name and offset of the variable).
	 */
	list<pair<string,int>> variables;
	
	/**
	 * The parameters of the function
	 */
	list<Parameter*> parameters;
	
	/**
	 * The number of bytes required on the stack to hold all of the variables of
	 * the function.
	 */
	int stackSpace;
};

class FunctionTable {
	public:
		/**
		 * Returns the stack sace required for a function with the given name.
		 * Returns -1 if there is no function with the given name.
		 *
		 * @param name The name of the function to lookup
		 * @return The size of the stack required for the function.
		 */
		int GetStackSpace(string name);
		
		/**
		 * Adds a function with the given name to the table
		 *
		 * @param fname The name of the function to add
		 * @param hasReturn Indicates if the function has a return value
		 */
		void AddFunction(string fname, bool hasReturn = false);
		
		/**
		 * Gets a reference to a function with the given name.
		 *
		 * @param name The name of the function
		 * @return A reference to the function
		 */
		Function* GetFunction(string name);
		
		/**
		 * Adds a variable to the list of variables for the given function and 
		 * calculates its offset.
		 *
		 * @param fname The function name
		 * @param vname The variable name
		 * @param size The size of the variable in bytes
		 */
		void AddVariable(string fname, string vname, int size);
		
		/**
		 * Adds a parameter to the given function
		 *
		 * @param fname The function name
		 * @param pname The parameter name
		 * @param byValue Indicates if the parameter is passed by value or reference
		 */
		void AddParameter(string fname, string pname, bool byValue);
		
		/**
		 * Gets the offset of a given variable within a given function
		 *
		 * @param fname The function name
		 * @param vname The variable name
		 * @return The variable's offset
		 */
		int GetVarOffset(string fname, string vname);
		
	private:
		map<string, Function*> functions;
};

#endif // ! FUNCTIONTABLE_H

/**
 * AddressTest.cpp
 *
 * The purpose of this file is only for testing the address table.
 */
 
#include <iostream>

#include "AddressTable.h"

int main()
{
	AddressTable addtab;
	
	cout << endl << endl << "Register test: " << endl;
	addtab.Add("var1", "$t0");
	addtab.Add("var2", "$t1");	
	addtab.Add("var3", "$t2");
	addtab.Add("var4", "$t3");
	addtab.Print();
	
	cout << endl << "Memory test: " << endl;
	addtab.Add("var5", 0);
	addtab.Add("var6", 4);
	addtab.Add("var7", 8);
	addtab.Add("var8", 12);
	addtab.Print();
	
	cout << endl << "Both test: " << endl;
	addtab.Add("var9", "$t4", 16);
	addtab.Add("var10", "$t5", 20);
	addtab.Add("var11", "$t6", 24);
	addtab.Add("var12", "$t7", 28);
	addtab.Print();
	
	return 0;
}

/**
 * AddressTest.cpp
 *
 * The purpose of this file is only for testing the address table.
 */
 
#include <iostream>

#include "AddressTable.h"
#include "RegAllocTable.h"

int main()
{
	RegAllocTable regtab(8, "$t");
	AddressTable addtab(&regtab);
	
	bool isNew;
	
    fstream fout;
    fout.open("addr_test.out", std::ios_base::out);
    regtab.SetFstream(&fout);
    addtab.SetFstream(&fout);
	
	cout << endl << endl << "Register test: " << endl;
	addtab.Add("var1", regtab.GetRegister("var1", isNew));
	addtab.Add("var2", regtab.GetRegister("var2", isNew));	
	addtab.Add("var3", regtab.GetRegister("var3", isNew));
	addtab.Add("var4", regtab.GetRegister("var4", isNew));
	addtab.Print();
	
	cout << endl << "Memory test: " << endl;
	addtab.Add("var5", 0);
	addtab.Add("var6", 4);
	addtab.Add("var7", 8);
	addtab.Add("var8", 12);
	addtab.Print();
	
	cout << endl << "Both test: " << endl;
	addtab.Add("var9", regtab.GetRegister("var9", isNew), 16);
	addtab.Add("var10", regtab.GetRegister("var10", isNew), 20);
	addtab.Add("var11", regtab.GetRegister("var11", isNew), 24);
	addtab.Add("var12", regtab.GetRegister("var12", isNew), 28);
	addtab.Print();
	
	cout << endl << "Load test: " << endl << endl;
	string reg = addtab.Load("var5");
	cout << "var5 is now in register " << reg << endl;
	reg = addtab.Load("var6");
	cout << "var6 is now in register " << reg << endl;
	reg = addtab.Load("var7");
	cout << "var7 is now in register " << reg << endl;
	addtab.Print();
	
	cout << endl << "Store test" << endl << endl;
	addtab.Store("var7");
	cout << "var7 has now been stored" << endl;
	addtab.Store("var6");
	cout << "var6 has now been stored" << endl;
	addtab.Store("var5");
	cout << "var5 has now been stored" << endl;
	addtab.Print();
	regtab.PrintRegisters();
	
	return 0;
}

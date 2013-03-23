#include "SymTab.h"
ostream& operator << ( ostream &outStream, const SymbolInfo &inf)
{
    	outStream<< "\n ======================================= \n ";
    	outStream<<  "      SYMBOL CONTENTS                        ";
	outStream<< "\n ======================================= \n ";
	outStream<< " Symbol Name  :  " <<  inf.symbol_name << "\n ";
        outStream<< " Storage Class : " <<  inf.storage_class << endl;
        outStream<< " Type          : " <<  inf.symbolType->GetName();     
	return outStream; 
}



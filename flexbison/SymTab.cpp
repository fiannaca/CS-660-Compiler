/*
 * See the description in SymTab.h!
 */

#include "SymTab.h"
ostream& operator << ( ostream &outStream, const SymbolInfo &inf)
{
        int w = 15;
        outStream << "       " << setiosflags(ios::left) 
                  << setfill(' ') << setw(w)
                  << inf.symbol_name
                  << setfill(' ') << setw(w)
                  << inf.storage_class
                  << setfill(' ') << setw(w)
                  << inf.symbolType->GetName() 
                  << resetiosflags(ios::left) << endl;
        /*
    	outStream<< "\n ======================================= \n ";
    	outStream<<  "      SYMBOL CONTENTS                        ";
	outStream<< "\n ======================================= \n ";
	outStream<< " Symbol Name  :  " <<  inf.symbol_name << "\n ";
        outStream<< " Storage Class : " <<  inf.storage_class << endl;
        outStream<< " Type          : " <<  inf.symbolType->GetName(); 
        */

	return outStream; 
}



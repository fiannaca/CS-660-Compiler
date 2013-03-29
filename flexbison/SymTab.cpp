/*
 * See the description in SymTab.h!
 */

//#include "SymTab.h"

//CCompiler.h includes SymTab.h so it doesn't have to be included again. This
// is being included so that the SymTab can use the driver's error/warning
// channels
#include "CCompiler.h"

SymTab::SymTab(CCompiler* ref)
{
    driver = ref;
    currentLevel = 0 ;
    // Ensure the nodes are allocated on the heap !
    AVLTree<SymbolInfo> *node = new AVLTree<SymbolInfo>();
    symTable.push_back(*node);
}

//These two functions forward errors and warnings from the symbol table onto the
// driver so that all errors/warnings are handled in a standard manner
void SymTab::error(string msg)
{
    driver->error(msg);
}

void SymTab::warning(string msg)
{
    driver->warning(msg);
}

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



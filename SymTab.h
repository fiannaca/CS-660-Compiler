#ifndef _SYMTAB_H_
#define _SYMTAB_H_
#include <string>
#include <map>
#include <list>
using namespace std;
struct SymbolInfo
{
    string symbol_name;
	int flags;
		
};

class SymTab
{
     
	 private:
	     
	     list< map<string,SymbolInfo> >  symTable;
	 public:	
	     void insert_symbol(SymbolInfo symbolInfo);
	     void insert_symbol(SymbolInfo symbolInfo, int level);
	     int search_symbol(SymbolInfo &symbolInfo,int &level);
   	
};

#endif 

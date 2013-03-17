#include <iostream>
#include "SymTab.h"

void SymTab::insert_symbol(SymbolInfo symbolInfo)
{
	
	/*
	  symbol table is completely empty  
	*/
	if( symTable.empty())
	{
		 map<string,SymbolInfo> item ; 
		 item[symbolInfo.symbol_name] = symbolInfo;
		 symTable.push_back(item);
		 
	}
	else 
	{
		map<string,SymbolInfo>  item =  symTable.back();
		item[symbolInfo.symbol_name] = symbolInfo;
		symTable.pop_back();
		symTable.push_back(item) ;
	    
	}
}
void SymTab::insert_symbol(SymbolInfo symbolInfo,int level)
{
	
	
	/*
	  symbol table is completely empty  
	*/
	
	std::list< map<string,SymbolInfo> >::iterator sym_ptr;
	sym_ptr = symTable.begin(); 
	while( sym_ptr != symTable.end() && ( level > 0 ) )
	{
		
		--level;
		sym_ptr++;
	}
	map<string,SymbolInfo>  item =  *sym_ptr;
	item[symbolInfo.symbol_name] = symbolInfo;
	symTable.erase(sym_ptr);
	symTable.insert(sym_ptr, item) ;
	    
	
}
int  SymTab::search_symbol(SymbolInfo &symbolInfo , int &level)
{
	int cur_level = 0 ; 
	std::list< map<string,SymbolInfo> >::iterator sym_ptr;
	sym_ptr = symTable.begin(); 
	while (sym_ptr != symTable.end() )
	{  
	   
	   
	   map<string,SymbolInfo> current_item = *sym_ptr; 
	   map<string,SymbolInfo>::iterator map_ptr ;
	   map_ptr = current_item.find(symbolInfo.symbol_name); 
	   if ( map_ptr != current_item.end() )
	   {
	   	   
		   // symbolInfo = *map_ptr[symbolInfo.symbol_name];
	   	   level  = cur_level; 
	   }
	   sym_ptr++;
	   cur_level++;	
	}
    return 0 ;    
}

void SymTab::dump_table()
{
    // Stub 	
}

void SymTab::dump_table(int level)
{
    // Stub 	
}

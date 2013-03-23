/*
 *
 *
 *
 *
 *
 */


#ifndef _SYMTAB_H_
#define _SYMTAB_H_
#include <string>
#include "AvlTree.h" 
#include "Type.h"
#include <list>
#include <vector>
using namespace std;

struct SymbolInfo
{
    string symbol_name;
    Type *symbolType; 
    int type_qualifier; 
    string function_name; 
    bool struct_union_name;
    bool isStrunctOrUnionItem; 
    int typeTableIndex;           
    int storage_class;
    int flags;
    friend ostream& operator << ( ostream &outStream , const SymbolInfo &inf);
	 
    int operator <( SymbolInfo inf)
    {
       return this->symbol_name < inf.symbol_name ;
    }
    int operator == ( SymbolInfo inf)
    {
       return ( this->symbol_name.compare(inf.symbol_name) == 0 ) ;
    }
    int operator > ( SymbolInfo inf)
    {
       return this->symbol_name > inf.symbol_name;
    }
    
		
};
class SymTab
{
     
	 private:
	     int currentLevel;   
	     vector< AVLTree<SymbolInfo> >  symTable;
	 public:
             SymTab()
	     {
	           currentLevel = 0 ;
                   // Ensure the nodes are allocated on the heap !
		   AVLTree<SymbolInfo> *node = new AVLTree<SymbolInfo>();
		   symTable.push_back(*node);  
	     }	  
	     void EnterScope()
	     {
	         ++currentLevel;
		 AVLTree<SymbolInfo> *node = new AVLTree<SymbolInfo>(); 
		 symTable.push_back(*node); 

	     }   
	     void LeaveScope()
	     {
	         --currentLevel;
		 AVLTree<SymbolInfo> *node;
		 *node = symTable[currentLevel];
		 delete(node);
                 symTable.pop_back(); 
	     }
	     void insert_symbol(SymbolInfo symbolInfo)
	     {
	         symTable[currentLevel].Insert(symbolInfo);           
	     }
	     void insert_symbol(SymbolInfo symbolInfo, int level)
	     {
	         symTable[level].Insert(symbolInfo);  
		     
	     }
	     bool find_symbol(SymbolInfo symbolInfo,int &level)
	     {
	         for ( int levelIndex = 0 ; levelIndex  <= currentLevel ; levelIndex++)
			 {
			 	if( symTable[levelIndex].Contains(symbolInfo) )
			 	{
			 		level = levelIndex;
			 		return true; 
			 	}
			 }    
	         return false; 
	     }
   	     void dump_table()
	     {
	         for ( int level = 0 ; level <= currentLevel ; level++)
		 {
		     symTable[level].Dump(); 
		 }
	     }
             void dump_table(int level)
	     {
	          symTable[level].Dump();  
	     }  
             
};

#endif 

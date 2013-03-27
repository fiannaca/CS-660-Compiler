/*
 * This is the symbol table class. It uses a stack of AVL Trees to organize the symbols. The AVL Tree is a data
 * structure which is guaranteed to be a balanced binary tree. For more info on the AVL Tree, see the header
 * AVLTree.h.
 * 
 * Note: the "stack" of AVL Trees, is in actuality an STL list of AVL Trees, since the same functionality as a stack
 * is easier to implement with the STL list.
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
    bool isEnumConst ;
    bool struct_union_name;
    bool isStrunctOrUnionItem; 
    int typeTableIndex;           
    int storage_class;
    int flags;
    friend ostream& operator << ( ostream &outStream , const SymbolInfo &inf);
    SymbolInfo()
    {
       this->symbol_name = "";
       this->symbolType = NULL;
       this->storage_class  = AUTO ;
       this->isEnumConst= false;      
    }  	 
    SymbolInfo(const SymbolInfo &sym)
    {
       this->symbol_name = sym.symbol_name;
       this->symbolType = sym.symbolType; 
       this->storage_class = sym.storage_class;
       this->type_qualifier = sym.type_qualifier;  
    }     
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
    string GetKey()
    {
       return this->symbol_name; 
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
		 
                 if ( currentLevel > 0 ) 
                 {  
                   
                   symTable.pop_back(); 
                 } 
	     }
	     void insert_symbol(SymbolInfo symbolInfo)
	     {
	          int level; 
                  if( find_symbol(symbolInfo,level)) 
                  {
                         std::cout<<"\n Shadowing variable ... " << symbolInfo.symbol_name<<"\n";
                  } 

                  if( symbolInfo.symbol_name != "")    
                    symTable[currentLevel].Insert(symbolInfo);           
	     }
	     void insert_symbol(SymbolInfo symbolInfo, int level)
	     {
	         if(symbolInfo.symbol_name != "")
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
		          cout<< endl << " AT LEVEL    " <<level ;   
                          symTable[level].Dump(); 
		 }
	     }
             void dump_table(int level)
	     {
	          symTable[level].Dump();  
	     }  
             
};

#endif 

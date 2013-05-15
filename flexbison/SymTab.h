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
#include <map> 

using namespace std;

struct SymbolInfo
{
    string symbol_name;
    Type *symbolType; 
    int type_qualifier; 
    string function_name;
    int offset;  
    bool isEnumConst ;
    bool struct_union_name;
    bool isStrunctOrUnionItem; 
    int typeTableIndex;           
    int storage_class;
    int flags;
    //int lineNum;
    //int colNum;

    friend ostream& operator << ( ostream &outStream , const SymbolInfo &inf);

    SymbolInfo()
    {
       this->symbol_name = "";
       this->symbolType = NULL;
       this->storage_class  = AUTO ;
       this->isEnumConst= false;
       this->offset = 0 ;       
       //this->lineNum = -1;
    }

    SymbolInfo(const SymbolInfo &sym)
    {
       this->symbol_name = sym.symbol_name;
       this->symbolType = sym.symbolType; 
       this->storage_class = sym.storage_class;
       this->type_qualifier = sym.type_qualifier;
       //this->lineNum = sym.lineNum; 
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

class CCompiler;

class SymTab
{
	 private:
	     int currentLevel;   
	     vector< AVLTree<SymbolInfo> >  symTable;
             map<int,int> offsetMap; 
             CCompiler* driver;
             void error(string msg);
             void warning(string msg);
	     list<string> funcNames;
	     map<string, AVLTree<SymbolInfo> > funcSymMap; 
	     map<string,int> funOffMap;
	 public:
             SymTab(CCompiler* ref);
             SymTab()
	     {
	           currentLevel = 0 ;
                   offsetMap[currentLevel] = 0 ;     
                   // Ensure the nodes are allocated on the heap !
		   AVLTree<SymbolInfo> *node = new AVLTree<SymbolInfo>();
		   symTable.push_back(*node);  
	     }	  
	     void EnterScope()
	     {
	             currentLevel = 1;
		     offsetMap[currentLevel] = 0 ; 
             AVLTree<SymbolInfo> *node = new AVLTree<SymbolInfo>(); 
		     symTable.push_back(*node); 

	     }   
	     void LeaveScope()
	     {
	         currentLevel = 0 ;
		 
             if ( currentLevel > 0 ) 
             {
               symTable.pop_back(); 
             }
	     }
	     void map_function_vars(const string &funcName)
	     {
		//cout<<funcName;
		if ( currentLevel >=  0 )  
		{
		   funcSymMap[funcName] = symTable[currentLevel];
		   funOffMap[funcName] = offsetMap[currentLevel];
		}
		funcSymMap[funcName].Dump();
		//cout<< "<Offset>"<< funOffMap[funcName]; 
		//cout<< "<Offset2>"<< offsetMap[currentLevel]; 
	     }
	    
	     void insert_symbol(SymbolInfo symbolInfo)
	     {
	          int level; 
                  if( find_symbol(symbolInfo,level)) 
                  {
                         //driver->warning("Shadowed variable");
                         //cout << "Shadowing variable ... " << symbolInfo.symbol_name << endl;
                         this->warning("Shadowing variable: " + symbolInfo.symbol_name);
                  } 

                  if( symbolInfo.symbol_name != "")    
                    symTable[currentLevel].Insert(symbolInfo); 
                    
                    //TODO Should offsets be added in here as well?          
	     }
	     void insert_symbol(SymbolInfo symbolInfo, int level)
	     {
	         if(symbolInfo.symbol_name != "")
                  { 
                    
                     if ( symbolInfo.symbolType != NULL ) 
                     {
                         //Alex 4/21 - I reversed the order of these so that the offset is increased after
                          symbolInfo.offset = offsetMap[currentLevel]; 
                          offsetMap[currentLevel] +=  symbolInfo.symbolType->GetSize();
                     }  
                     symTable[level].Insert(symbolInfo);   
		  }  
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

             SymbolInfo* fetch_symbol(SymbolInfo symbolInfo,int level)
	     {
	             return symTable[level].Fetch(symbolInfo);
			 	
	     }
             SymbolInfo* fetch_symbol(SymbolInfo symbolInfo)
	     {
	             
                   SymbolInfo *info = NULL ; 
                   info = symTable[currentLevel].Fetch(symbolInfo);
                   if ( info == NULL )
                   {
                       info = symTable[0].Fetch(symbolInfo);
     
                   }
                   return  info; 			  	
	     }
                
              

   	     void dump_table()
	     {
                 int w = 15;

                 cout << endl 
                      << setw(50) << setfill('=') << "=" << endl
                      << "SYMBOL TABLE CONTENTS:" << endl;

                 cout << endl;

	         for ( int level = 0 ; level <= currentLevel ; level++)
		 {
		          cout << setw(4) << setfill(' ')
                               << "L" << level << ": "
                               << setiosflags(ios::left) 
                               << setw(w) << setfill(' ') 
                               << "Name" 
                               << setw(w) << setfill(' ')
                               << "Storage Class"
                               << setw(w) << setfill(' ')
                               << "Type" 
                               << resetiosflags(ios::left) << endl;

                          symTable[level].Dump(); 

                          cout << endl;
		 }

                 cout << setw(50) << setfill('=') << "=" << endl;
	     }

             void dump_table(int level)
	     {
	          symTable[level].Dump();  
	     }  
             list<SymbolInfo> GetGlobals()
	     {
		  return symTable[0].GetElements();
	     }
	     list<SymbolInfo> GetLocals(string &funcName)
	     {
		  return funcSymMap[funcName].GetElements();
	     }
             bool IsGlobal(string &symName)
	     {
		 SymbolInfo inf; 
		 int level ; 
		 bool exists =  false;
		 inf.symbol_name = symName ; 
		 exists = find_symbol(inf,level);
		 return ( exists && ( level == 0 ));
		 
	     } 
	     int GetFuncOffset(string &funcName)
	     {
		 
		return funOffMap[funcName] ;
	     }
            
};

#endif 

#ifndef _SYMTAB_H_
#define _SYMTAB_H_
#include <string>
#include <map>
#include <list>
#include <vector>
using namespace std;

enum STORAGE_CLASS
{
   EXTERN ,
   STATIC ,
   REGISTER ,
   AUTO	

};

enum  BASIC_TYPES
{
   INT,
   CHAR ,
   FLOAT,
   DOUBLE,
   STRUCT,
   UNION	

};

struct TypeInfo
{
    list<int> typeList; 	
};

struct SymbolInfo
{
    string symbol_name;
    bool struct_union_name;
    bool isStrunctOrUnionItem; 
	int typeTableIndex;           
    int storage_class;
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
   	     void dump_table();
         void dump_table(int level);  
        vector<TypeInfo> typeTable;
};

#endif 

#ifndef _AST_IDLLIST_H_
#define _AST_IDLLIST_H_
#include "AstStatement.h"
using namespace std; 
class AstIDList : public AST
{
	
    AstID  *id;
	AstIDList *idlist;
public:
	AstIDList( AstID *id , AstIDList *idlist)
	{
		this->id = id; 
		this->idlist = idlist ; 
	}
	void Visit()
	{
		
	} 
	
};


#endif 

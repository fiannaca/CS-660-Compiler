#ifndef _AST_INITLLIST_H_
#define __AST_INITLLIST_H_
#include "AstStatement.h"
using namespace std; 
class AstInitList : public AST 
{


	AstInitializer *intializer;
	AstInitList *list;
public:
	AstInitList( AstInitList *intializer  , AstInitList *list)
	{
		this->intializer = intializer ; 
		this->list =  list ; 
	}
	void Visit()
	{
		
	} 
	
};


#endif 

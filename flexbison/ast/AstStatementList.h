#ifndef _AST_STATEMENT_LIST_H_
#define _AST_STATEMENT_LIST_H_
#include "AstStatement.h"
#include <list>
using namespace std; 
class AstStatementList
{
	AstStatement *list; 
public:
	AstStatementList( AstStatement *stmt)
	{
		this->list= stmt ;
	}
	void Visit()
	{
		
	} 
	
};


#endif 

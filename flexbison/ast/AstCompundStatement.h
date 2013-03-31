#ifndef _AST_COMPOUND_H_
#define _AST_COMPOUND_H_
#include "AstStatement.h"
#include <list>
using namespace std; 
class AstCompund : public AstStatement 
{
	AstDeclList *dlist;
	AstStatementList *slist; 
public:
	AstCompund( AstDeclList *dlist , AstStatmenetList *slist)
	{
		this->dlist  = dlist;
		this->slist = slist; 
	}
	void Visit()
	{
		
	} 
	
};

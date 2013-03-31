#ifndef _AST_TYPEQUALIST__H_
#define _AST_TYPEQUALIST__H_
#include "AstStatement.h"
using namespace std; 
class AstTypeQualList : public AstStatement 
{
	string type_qual; 
	AstTypeQualList *list;
public:
	AstTypeQualList( string type_qual , AstTypeQualList *list)
	{
		this->type_qual= type_qual ;
		this->list = list; 
	}
	void Visit()
	{
		
	} 
	
};


#endif 

#ifndef _AST_DOWHILE_
#define _AST_DOWHILE_
#include "AstExpression.h"
#include "AstStatement.h"
class AstDoWhile : public AstStatement
{
	AstExpression *test;
	AstStatement *statement; 
public:
    AstDoWhile( AstExpression *test, AstStatement *statement )
    {
    	this->statement = statement;
    	this->test = test; 
    }
	void Visit()
	{
		
	}
};

#endif 

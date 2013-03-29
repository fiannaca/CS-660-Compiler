#ifndef _AST_IF_STATMENT
#define _AST_IF_STATMENT
#include "AstExpression.h"
#include "AstStatement.h"
class ASTIFStatement: public AstStatement 
{
	
   	AstExpression *test ; 
    AstStatement *statement;
    AstStatement *elseStatement;
    
public: 	
	ASTIFStatement( AstExpression *test , AstStatement *statement , AstStatement *elseStatement )
	{
		this->test = test;
		this->statement = statement;
		this->elseStatement = elseStatement; 
	}
	void Vist()
	{
		
	}
};

#endif 


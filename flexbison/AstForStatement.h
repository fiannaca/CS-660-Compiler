#ifndef _AST_FOR_STATMENT_
#define _AST_FOR_STATMENT_
#include "AstExpression.h"
#include "AstStatment.h"
class AstFor: public AstStatement
{
     AstExpression *init;
     AstExpression *test;
     AstExpressoin *increment;
     AstStatment *statment; 
public:
	 AstFor(AstExpression *init , AstExpression *test , AstExpression *increment , AstStatment *statement)
	 {
	 	this->init =init ;
	 	this->test =test;
	 	this->increment = increment;
	 	this->statement = statement; 
	 	
	 }
     void Visit();     

   	
	
};


#endif 

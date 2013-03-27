#ifdef _AST_CASE_
#define _AST_CASE_
#include "AstExpression.h"
#include "AstStatement.h"
class AstCase : public AstStatement
{
	AstExpression *expression;
	AstStatement *stamtent ; 
public:
	AstStatement( AstExpresison *exp , AstStatement *stmt)
	{
		this->expression = exp;
		this->statement = stmt;
	}
	void Visit()
	{
		
	}
	
};
#endif 


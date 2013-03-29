#ifdef _AST_DEFAULT_
#define _AST_DEFAULT_
#include "AstExpression.h"
#include "AstStatement.h"
class AstDefault : public AstStatement
{

	AstStatement *stamtent ; 
public:
	AstDefault( AstExpresison *exp , AstStatement *stmt)
	{
	
		this->statement = stmt;
	}
	void Visit()
	{
		
	}
	
};
#endif 


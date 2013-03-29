#ifndef _AST_RETURN_STATEMENT_
#define _AST_RETURN_STATMENT_
#include "AstStatement.h"
#include "AstExpression.h"
class AstReturn : public AstStatement
{
   
    AstExpression *returnExpression;

    public:
    
    AstReturn(AstExpression *returnExpression)
    {
        this->returnExpression = returnExpression; 

        this->setLabel("ReturnStatement");
    }

    void Visit()
    {
        AST::vis.addNode(this->getUID(), this->getLabel());
        AST::vis.addEdge(this->getUID(), returnExpression->getLabel());
    }
};
 


#endif 

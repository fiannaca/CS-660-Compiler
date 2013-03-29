#ifndef _AST_IF_STATMENT
#define _AST_IF_STATMENT
#include "AstExpression.h"
#include "AstStatement.h"
class AstIfStatement: public AstStatement 
{
	
    AstExpression *test ; 
    AstStatement *statement;
    AstStatement *elseStatement;
    
    public: 	
    
    AstIfStatement( AstExpression *test , AstStatement *statement , AstStatement *elseStatement )
    {
        this->test = test;
        this->statement = statement;
        this->elseStatement = elseStatement;

        this->setLabel("IfStatement");
    }

    void Vist()
    {
        AST::vis.addNode(this->getUID(), this->getLabel());
        AST::vis.addEdge(this->getUID(), test->getUID());
        AST::vis.addEdge(this->getUID(), statement->getUID());
        AST::vis.addEdge(this->getUID(), elseStatement->getUID());
    }
};

#endif 


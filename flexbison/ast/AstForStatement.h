#ifndef _AST_FOR_STATMENT_
#define _AST_FOR_STATMENT_
#include "AstExpression.h"
#include "AstStatement.h"
class AstFor: public AstStatement
{
    AstExpression *init;
    AstExpression *test;
    AstExpression *increment;
    AstStatement *statement; 

    public:

    AstFor(AstExpression *init , AstExpression *test , AstExpression *increment , AstStatement *statement)
    {
        this->init =init ;
        this->test =test;
        this->increment = increment;
        this->statement = statement; 

        this->setLabel("ForStatement");
    }

    void Visit()
    {
        AST::vis.addNode(this->getUID(), this->getLabel());
        AST::vis.addEdge(this->getUID(), init->getUID());
        AST::vis.addEdge(this->getUID(), test->getUID());
        AST::vis.addEdge(this->getUID(), increment->getUID());
        AST::vis.addEdge(this->getUID(), statement->getUID());
    }	
};

#endif

#ifndef _AST_WHILE_
#define _AST_WHILE_
#include "AstExpression.h"
#include "AstStatement.h"
class AstDo : public AstStatement
{
    AstExpression *test;
    AstStatement *statement; 

    public:
    
    AstDo( AstExpression *test, AstStatement *statement )
    {
        this->statement = statement;
        this->test = test;

        this->setLabel("WhileStatement");
    }

    void Visit()
    {
        AST::vis.addNode(this->getUID(), this->getLabel());
    }
};

#endif 

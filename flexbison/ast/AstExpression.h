#ifndef _AST_EXPRESSION_
#define _AST_EXPRESSION_

#include "Ast.h"
#include "AstConstants.h"
#include "AstID.h"

class AstExpression : public AST
{
	
    public:
	void Visit()
	{
		
	}
};

class AstAssignExpr : public AST
{
    //This is a stub for the AssignExpr class - TODO implement later

    AstAssignExpr()
    {

    }

    void Visit()
    {

    }
};

class AstPrimaryExpr : public AST
{
    enum ExprType
    {
        ID,
        CONST,
        STRING,
        EXPR
    };

    ExprType type;

    AstID *id;
    AstConstant *constant;
    AstString *str;
    AstExpression *expr;

    public:
        AstPrimaryExpr(AstID* id)
        {
            this->id = id;
            this->constant = NULL;
            this->str = NULL;
            this->expr = NULL;
            this->type = ID;

            this->setLabel("PrimaryExpression");
        }

        AstPrimaryExpr(AstConstant* c)
        {
            this->id = NULL;
            this->constant = c;
            this->str = NULL;
            this->expr = NULL;
            this->type = CONST;

            this->setLabel("PrimaryExpression");
        }

        AstPrimaryExpr(AstString* s)
        {
            this->id = NULL;
            this->constant = NULL;
            this->str = s;
            this->expr = NULL;
            this->type = STRING;

            this->setLabel("PrimaryExpression");
        }

        AstPrimaryExpr(AstExpression* e)
        {
            this->id = NULL;
            this->constant = NULL;
            this->str = NULL;
            this->expr = e;
            this->type = STRING;

            this->setLabel("PrimaryExpression");
        }

        void Visit()
        {
            AST::vis.addNode(this->getUID(), this->getLabel());
            
            switch(type)
            {
                case ID:
                    AST::vis.addEdge(this->getUID(), id->getUID());
                    break;

                case CONST:
                    AST::vis.addEdge(this->getUID(), constant->getUID());
                    break;

                case STRING:
                    AST::vis.addEdge(this->getUID(), str->getUID());
                    break;

                case EXPR:
                    AST::vis.addEdge(this->getUID(), expr->getUID());
                    break;
            }
        }
};

class AstArgExprList : public AST
{
    AstArgExprList *list;
    AstAssignExpr *expr;
    bool isLastItem;

    public:
        AstArgExprList(AstArgExprList *list, AstAssignExpr *expr)
        {
            this->list = list;
            this->expr = expr;
            this->isLastItem = false;

            this->setLabel("ArgumentExpressionList");            
        }

        AstArgExprList(AstAssignExpr *expr)
        {
            this->list = NULL;
            this->expr = expr;
            this->isLastItem = true;

            this->setLabel("ArgumentExpressionList");
        }

        void Visit()
        {
            AST::vis.addNode(this->getUID(), this->getLabel());
            AST::vis.addEdge(this->getUID(), expr->getUID());
            
            if(!this->isLastItem)
            {
                AST::vis.addEdge(this->getUID(), list->getUID());
            }
        }
};

#endif 

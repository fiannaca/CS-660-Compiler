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

class AstNodeStub : public AST
{
    //Place the children nodes here

    public:
        //Constructor
        AstNodeStub()
        {
            this->setLabel("");
        }

        //Traversal
        void Visit()
        {
            //Visit children nodes

            //Output visualization
            //AST::vis.addNode(this->getUID(), this->getLabel());
            //AST::vis.addEdge(this->getUID(), child->getUID());

            //Output 3AC
        }
};

class AstAssignExpr : public AST
{
    //TODO implement later

    //Place the children nodes here

    public:
        //Constructor
        AstAssignExpr()
        {
            this->setLabel("AssignmentExpression");
        }

        //Traversal
        void Visit()
        {
            //Visit children nodes

            //Output visualization
            //AST::vis.addNode(this->getUID(), this->getLabel());
            //AST::vis.addEdge(this->getUID(), child->getUID());

            //Output 3AC
        }
};

class AstCastExpr : public AST
{
    //TODO implement later

    //Place the children nodes here

    public:
        //Constructor
        AstCastExpr()
        {
            this->setLabel("CastExpression");
        }

        //Traversal
        void Visit()
        {
            //Visit children nodes

            //Output visualization
            //AST::vis.addNode(this->getUID(), this->getLabel());
            //AST::vis.addEdge(this->getUID(), child->getUID());

            //Output 3AC
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
            switch(type)
            {
                case ID:
                    id->Visit();

                    AST::vis.addNode(this->getUID(), this->getLabel());
                    AST::vis.addEdge(this->getUID(), id->getUID());

                    //Output 3AC
                    break;

                case CONST:
                    constant->Visit();

                    AST::vis.addNode(this->getUID(), this->getLabel());
                    AST::vis.addEdge(this->getUID(), constant->getUID());

                    //Output 3AC
                    break;

                case STRING:
                    str->Visit();

                    AST::vis.addNode(this->getUID(), this->getLabel());
                    AST::vis.addEdge(this->getUID(), str->getUID());

                    //Output 3AC
                    break;

                case EXPR:
                    expr->Visit();

                    AST::vis.addNode(this->getUID(), this->getLabel());
                    AST::vis.addEdge(this->getUID(), expr->getUID());

                    //Output 3AC
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
            //Visit children nodes
            if(!isLastItem)
            {
                list->Visit();
            }

            expr->Visit();

            //Output visualization
            AST::vis.addNode(this->getUID(), this->getLabel());
            AST::vis.addEdge(this->getUID(), expr->getUID());
            
            if(!this->isLastItem)
            {
                AST::vis.addEdge(this->getUID(), list->getUID());
            }

            //Output 3AC
        }
};

class AstPostfixExpr : public AST
{
    public:
	enum Operator
	{
	    NONE,
	    DOT_OP,
	    PTR_OP,
	    INC_OP,
	    DEC_OP
	};

        enum Type
        {
            PRIMARY,
            BRACKETS,
            EMPTY_PARENS,
            PARENS,
            DOT,
            PTR,
            INC,
            DEC
        };
  
    private:

    //Place the children nodes here
    AstPrimaryExpr *priexpr;
    AstPostfixExpr *ptfExpr;
    AstExpression  *brakExpr;
    AstArgExprList *argExprList;
    AstID          *id;
    Operator       op;

    //Identifies which production we are in so that the proper 3AC can be written
    Type t;

    public:

        //Constructor
        AstPostfixExpr(AstPrimaryExpr* p)
        {
            this->priexpr = p;
            this->ptfExpr = NULL;
            this->brakExpr = NULL;
            this->argExprList = NULL;
            this->id = NULL;
            this->op = NONE;
            
            this->t = PRIMARY;

            this->setLabel("AstPostfixExpr - Primary");
        }

        AstPostfixExpr(AstPostfixExpr* p, AstExpression* e)
        {
            this->priexpr = NULL;
            this->ptfExpr = p;
            this->brakExpr = e;
            this->argExprList = NULL;
            this->id = NULL;
            this->op = NONE;
            
            this->t = BRACKETS;

            this->setLabel("AstPostfixExpr - Brackets");
        }

        AstPostfixExpr(AstPostfixExpr* p)
        {
            this->priexpr = NULL;
            this->ptfExpr = p;
            this->brakExpr = NULL;
            this->argExprList = NULL;
            this->id = NULL;
            this->op = NONE;
            
            this->t = EMPTY_PARENS;

            this->setLabel("AstPostfixExpr - Empty Parens");
        }

        AstPostfixExpr(AstPostfixExpr *p, AstArgExprList *a)
        {
            this->priexpr = NULL;
            this->ptfExpr = p;
            this->brakExpr = NULL;
            this->argExprList = a;
            this->id = NULL;
            this->op = NONE;
            
            this->t = PARENS;

            this->setLabel("AstPostfixExpr - Parens");
        }

        AstPostfixExpr(AstPostfixExpr *p, Operator o, AstID *i)
        {
            this->priexpr = NULL;
            this->ptfExpr = p;
            this->brakExpr = NULL;
            this->argExprList = NULL;
            this->id = i;
            this->op = o;
            
            if(o == DOT_OP)
                this->t = DOT;
            else
                this->t = PTR;

            this->setLabel("AstPostfixExpr - Dot or Ptr");
        }

        AstPostfixExpr(AstPostfixExpr *p, Operator o)
        {
            this->priexpr = NULL;
            this->ptfExpr = p;
            this->brakExpr = NULL;
            this->argExprList = NULL;
            this->id = NULL;
            this->op = o;
            
            if(o == INC_OP)
                this->t = INC;
            else
                this->t = DEC;

            this->setLabel("AstPostfixExpr - Inc or Dec");
        }

        //Traversal
        void Visit()
        {
            switch(t)
            {
                case PRIMARY:
                    //Visit children nodes
                    priexpr->Visit();

                    //Output visualization
                    AST::vis.addNode(this->getUID(), this->getLabel());
                    AST::vis.addEdge(this->getUID(), priexpr->getUID());

                    //Output 3AC
                    
                    break;

                case BRACKETS:
                    //Visit children nodes
                    ptfExpr->Visit();
                    brakExpr->Visit();

                    //Output visualization
                    AST::vis.addNode(this->getUID(), this->getLabel());
                    AST::vis.addEdge(this->getUID(), ptfExpr->getUID());
                    AST::vis.addEdge(this->getUID(), brakExpr->getUID());

                    //Output 3AC
                    
                    break;

                case EMPTY_PARENS:
                    //Visit children nodes
                    ptfExpr->Visit();

                    //Output visualization
                    AST::vis.addNode(this->getUID(), this->getLabel());
                    AST::vis.addEdge(this->getUID(), ptfExpr->getUID());

                    //Output 3AC
                    
                    break;

                case PARENS:
                    //Visit children nodes
                    ptfExpr->Visit();
                    argExprList->Visit();

                    //Output visualization
                    AST::vis.addNode(this->getUID(), this->getLabel());
                    AST::vis.addEdge(this->getUID(), ptfExpr->getUID());
                    AST::vis.addEdge(this->getUID(), argExprList->getUID());

                    //Output 3AC
                    
                    break;

                case DOT:
                    //Visit children nodes
                    ptfExpr->Visit();
                    id->Visit();

                    //Output visualization
                    AST::vis.addNode(this->getUID(), this->getLabel());
                    AST::vis.addEdge(this->getUID(), ptfExpr->getUID());
                    AST::vis.addEdge(this->getUID(), id->getUID());

                    //Output 3AC
                    
                    break;

                case PTR:
                    //Visit children nodes
                    ptfExpr->Visit();
                    id->Visit();

                    //Output visualization
                    AST::vis.addNode(this->getUID(), this->getLabel());
                    AST::vis.addEdge(this->getUID(), ptfExpr->getUID());
                    AST::vis.addEdge(this->getUID(), id->getUID());

                    //Output 3AC
                    
                    break;

                case INC:
                    //Visit children nodes
                    ptfExpr->Visit();

                    //Output visualization
                    AST::vis.addNode(this->getUID(), this->getLabel());
                    AST::vis.addEdge(this->getUID(), ptfExpr->getUID());

                    //Output 3AC
                    
                    break;

                case DEC:
                    //Visit children nodes
                    ptfExpr->Visit();

                    //Output visualization
                    AST::vis.addNode(this->getUID(), this->getLabel());
                    AST::vis.addEdge(this->getUID(), ptfExpr->getUID());

                    //Output 3AC
                    
                    break;
            }
        }
};


class AstUnaryExpr : public AST
{
    //Place the children nodes here
    AstPostfixExpr *expr;
    bool isINC;
    bool isDEC;
    AstUnaryOp   *op;
    AstCastExpr  *cast;
    AstUnaryExpr *uniexpr;
    AstTypeName  *tname;

    public:
        enum Type
        {
            POSTFIX,
            INC,
            DEC, 
            CAST,
            SIZEOF,
            SIZEOF_TYPE
        } t;

        //Constructor
        AstUnaryExpr(AstPostfixExpr *e)
        {
            this->expr = e;
            this->isINC = false;
            this->isDEC = false;
            this->op = NULL;
            this->cast = NULL;
            this->uniexpr = NULL;
            this->tname = NULL;
            this->t = POSTFIX;

            this->setLabel("UnaryExpression - Postfix");
        }

        AstUnaryExpr(AstUnaryExpr* e, bool inc)
        {
            this->expr = NULL;
            this->isINC = inc;
            this->isDEC = !inc;
            this->op = NULL;
            this->cast = NULL;
            this->uniexpr = e;
            this->tname = NULL;

            if(inc)
                this->t = INC;
            else
                this->t = DEC;

            this->setLabel("UnaryExpression - Inc or Dec");
        }

        AstUnaryExpr(AstUnaryOp* o, AstCastExpr* c)
        {
            this->expr = NULL;
            this->isINC = false;
            this->isDEC = false;
            this->op = o;
            this->cast = c;
            this->uniexpr = NULL;
            this->tname = NULL;

            this->t = CAST;

            this->setLabel("UnaryExpression - Cast");
        }

        AstUnaryExpr(AstUnaryExpr* e)
        {
            this->expr = NULL;
            this->isINC = false;
            this->isDEC = false;
            this->op = NULL;
            this->cast = NULL;
            this->uniexpr = e;
            this->tname = NULL;

            this->t = SIZEOF;

            this->setLabel("UnaryExpression - Sizeof");
        }

        AstUnaryExpr(AstTypeName* t)
        {
            this->expr = NULL;
            this->isINC = false;
            this->isDEC = false;
            this->op = NULL;
            this->cast = NULL;
            this->uniexpr = NULL;
            this->tname = t;

            this->t = SIZEOF_TYPE;

            this->setLabel("UnaryExpression - Sizeof Type");
        }

        //Traversal
        void Visit()
        {
            switch(t)
            {
                case POSTFIX:
                    //Visit children nodes
                    expr->Visit();

                    //Output visualization
                    AST::vis.addNode(this->getUID(), this->getLabel());
                    AST::vis.addEdge(this->getUID(), expr->getUID());

                    //Output 3AC
                    
                    break;

                case INC:
                    //Visit children nodes
                    uniexpr->Visit();

                    //Output visualization
                    AST::vis.addNode(this->getUID(), this->getLabel());
                    AST::vis.addEdge(this->getUID(), uniexpr->getUID());

                    //Output 3AC
                    
                    break;

                case DEC:
                    //Visit children nodes
                    uniexpr->Visit();

                    //Output visualization
                    AST::vis.addNode(this->getUID(), this->getLabel());
                    AST::vis.addEdge(this->getUID(), uniexpr->getUID());

                    //Output 3AC
                    
                    break;

                case CAST:
                    //Visit children nodes
                    op->Visit();
                    cast->Visit();

                    //Output visualization
                    AST::vis.addNode(this->getUID(), this->getLabel());
                    AST::vis.addEdge(this->getUID(), op->getUID());
                    AST::vis.addEdge(this->getUID(), cast->getUID());

                    //Output 3AC
                    
                    break;

                case SIZEOF:
                    //Visit children nodes
                    uniexpr->Visit();

                    //Output visualization
                    AST::vis.addNode(this->getUID(), this->getLabel());
                    AST::vis.addEdge(this->getUID(), uniexpr->getUID());

                    //Output 3AC
                    
                    break;

                case SIZEOF_TYPE:
                    //Visit children nodes
                    tname->Visit();

                    //Output visualization
                    AST::vis.addNode(this->getUID(), this->getLabel());
                    AST::vis.addEdge(this->getUID(), tname->getUID());

                    //Output 3AC
                    
                    break;
            }
        }
};
#endif 

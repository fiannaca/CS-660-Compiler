#include "Ast.h"

void AstExpression::Visit()
{

}

/*
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
*/

///////////////////////////////////////////////////////////////////////////////
// BEGIN: AstPrimaryExpr  /////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

AstPrimaryExpr::AstPrimaryExpr(AstID* id)
{
    this->id = id;
    this->constant = NULL;
    this->str = NULL;
    this->expr = NULL;
    this->type = ID;

    this->setLabel("PrimaryExpression");
}

AstPrimaryExpr::AstPrimaryExpr(AstConstant* c)
{
    this->id = NULL;
    this->constant = c;
    this->str = NULL;
    this->expr = NULL;
    this->type = CONST;

    this->setLabel("PrimaryExpression");
}

AstPrimaryExpr::AstPrimaryExpr(AstString* s)
{
    this->id = NULL;
    this->constant = NULL;
    this->str = s;
    this->expr = NULL;
    this->type = STRING;

    this->setLabel("PrimaryExpression");
}

AstPrimaryExpr::AstPrimaryExpr(AstExpression* e)
{
    this->id = NULL;
    this->constant = NULL;
    this->str = NULL;
    this->expr = e;
    this->type = STRING;

    this->setLabel("PrimaryExpression");
}

void AstPrimaryExpr::Visit()
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

///////////////////////////////////////////////////////////////////////////////
// BEGIN: AstArgExprList  /////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

AstArgExprList::AstArgExprList(AstArgExprList *list, AstAssignExpr *expr)
{
    this->list = list;
    this->expr = expr;
    this->isLastItem = false;

    this->setLabel("ArgumentExpressionList");            
}

AstArgExprList::AstArgExprList(AstAssignExpr *expr)
{
    this->list = NULL;
    this->expr = expr;
    this->isLastItem = true;

    this->setLabel("ArgumentExpressionList");
}

void AstArgExprList::Visit()
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

///////////////////////////////////////////////////////////////////////////////
// BEGIN: AstPostfixExpr  /////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

AstPostfixExpr::AstPostfixExpr(AstPrimaryExpr* p)
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

AstPostfixExpr::AstPostfixExpr(AstPostfixExpr* p, AstExpression* e)
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

AstPostfixExpr::AstPostfixExpr(AstPostfixExpr* p)
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

AstPostfixExpr::AstPostfixExpr(AstPostfixExpr *p, AstArgExprList *a)
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

AstPostfixExpr::AstPostfixExpr(AstPostfixExpr *p, Operator o, AstID *i)
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

AstPostfixExpr::AstPostfixExpr(AstPostfixExpr *p, Operator o)
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
void AstPostfixExpr::Visit()
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

///////////////////////////////////////////////////////////////////////////////
// BEGIN: AstUnaryExpr  ///////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

AstUnaryExpr::AstUnaryExpr(AstPostfixExpr *e)
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

AstUnaryExpr::AstUnaryExpr(AstUnaryExpr* e, bool inc)
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

AstUnaryExpr::AstUnaryExpr(AstUnaryOp* o, AstCastExpr* c)
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

AstUnaryExpr::AstUnaryExpr(AstUnaryExpr* e)
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

AstUnaryExpr::AstUnaryExpr(AstTypeName* t)
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
void AstUnaryExpr::Visit()
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

///////////////////////////////////////////////////////////////////////////////
// BEGIN: AstCastExpr  ////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

AstCastExpr::AstCastExpr(AstUnaryExpr* u)
{
    this->uniexpr = u;
    this->cast = NULL;
    this->tname = NULL;

    this->setLabel("CastExpression");
}

AstCastExpr::AstCastExpr(AstTypeName* t, AstCastExpr* c)
{
    this->uniexpr = NULL;
    this->cast = c;
    this->tname = t;

    this->setLabel("CastExpression");
}

//Traversal
void AstCastExpr::Visit()
{
    if(uniexpr)
    {
        //Visit children nodes
        uniexpr->Visit();

        //Output visualization
        AST::vis.addNode(this->getUID(), this->getLabel());
        AST::vis.addEdge(this->getUID(), uniexpr->getUID());

        //Output 3AC
    }
    else
    {
        //Visit children nodes
        tname->Visit();
        cast->Visit();

        //Output visualization
        AST::vis.addNode(this->getUID(), this->getLabel());
        AST::vis.addEdge(this->getUID(), tname->getUID());
        AST::vis.addEdge(this->getUID(), cast->getUID());

        //Output 3AC
    }
}


///////////////////////////////////////////////////////////////////////////////
// BEGIN: AstTypeName  ////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//TODO complete later
//Constructor
AstTypeName::AstTypeName()
{
    this->setLabel("TypeName");
}

//Traversal
void AstTypeName::Visit()
{
    //Visit children nodes

    //Output visualization
    //AST::vis.addNode(this->getUID(), this->getLabel());
    //AST::vis.addEdge(this->getUID(), child->getUID());

    //Output 3AC
}

///////////////////////////////////////////////////////////////////////////////
// BEGIN: AstString  //////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

AstString::AstString(string str)
{
    this->val = str;

    this->setLabel("StringLiteral");
}

void AstString::Visit()
{
    AST::vis.addNode(this->getUID(), this->getLabel());

    //Add an extra node to the visualization to see the actual data
    int tmp = Visualizer::GetNextUID();
    AST::vis.addNode(tmp, "Value: " + val);
    AST::vis.addEdge(this->getUID(), tmp);
}

///////////////////////////////////////////////////////////////////////////////
// BEGIN: AstConstant  ////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
    
AstConstant::AstConstant(int val)
{
    this->type = INT;
    this->ival = val;

    this->setLabel("IntegerConstant");
}

AstConstant::AstConstant(string val)
{
    this->type = CHAR;
    this->str = val;

    this->setLabel("CharacterConstant");
}

AstConstant::AstConstant(double val)
{
    this->type = FLOAT;
    this->dval = val;

    this->setLabel("FloatConstant");
}

AstConstant::AstConstant(int val, string name)
{
    this->type = ENUM;
    this->ival = val;
    this->str = name;

    this->setLabel("EnumerationConstant");
}

void AstConstant::Visit()
{
    AST::vis.addNode(this->getUID(), this->getLabel());

    //Add an extra node to the visualization to see the actual data
    stringstream ss;
    int tmp = Visualizer::GetNextUID();

    switch(this->type)
    {
        case INT:
            ss << "Value: " << ival;
            break;
    
        case CHAR:
            ss << "Value: " << str;
            break;

        case FLOAT:
            ss << "Value: " << dval;
            break;

        case ENUM:
            ss << "Name: " << str << ", Value: " << ival;
            break;
    }

    AST::vis.addNode(tmp, ss.str());
    AST::vis.addEdge(this->getUID(), tmp);
}

///////////////////////////////////////////////////////////////////////////////
// BEGIN: AstUnaryOp  /////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

AstUnaryOp::AstUnaryOp(Operator o)
{
    this->op = o;

    this->setLabel("UnaryOperator");
}

//Traversal
void AstUnaryOp::Visit()
{
    //Visit children nodes

    //Output visualization
    AST::vis.addNode(this->getUID(), this->getLabel());

    //Output 3AC
}

///////////////////////////////////////////////////////////////////////////////
// BEGIN: AstID  //////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

AstID::AstID(string s)
{
    this->str = s;

    this->setLabel("Identifier");
}

void AstID::Visit()
{
    AST::vis.addNode(this->getUID(), this->getLabel() + ": " + str);
}

///////////////////////////////////////////////////////////////////////////////
// BEGIN: AstMultExpr  ////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

AstMultExpr::AstMultExpr(AstCastExpr* c)
{
    this->cast = c;
    this->mult = NULL;
    this->op = NONE;

    this->setLabel("MultiplicativeExpression");
}

AstMultExpr::AstMultExpr(AstMultExpr* m, Operator o, AstCastExpr* c)
{
    this->cast = c;
    this->mult = m;
    this->op = o;

    this->setLabel("MultiplicativeExpression");
}

//Traversal
void AstMultExpr::Visit()
{
    //Visit children nodes
    if(mult)
        mult->Visit();

    cast->Visit();

    //Output visualization
    AST::vis.addNode(this->getUID(), this->getLabel());

    if(mult)
    {
        stringstream ss;
        int tmp = Visualizer::GetNextUID();
        char c = (op == STAR) ? '*' : ((op == DIV) ? '/' : '%');
        ss << c;

        AST::vis.addNode(tmp, ss.str());

        AST::vis.addEdge(this->getUID(), mult->getUID());
        AST::vis.addEdge(this->getUID(), tmp);
    }

    AST::vis.addEdge(this->getUID(), cast->getUID());

    //Output 3AC
}

///////////////////////////////////////////////////////////////////////////////
// BEGIN: AstAddExpr  /////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

AstAddExpr::AstAddExpr(AstMultExpr* m)
{
    this->mult = m;
    this->add = NULL;
    this->op = NONE;

    this->setLabel("AdditiveExpression");
}

AstAddExpr::AstAddExpr(AstAddExpr* a, Operator o, AstMultExpr* m)
{
    this->mult = m;
    this->add = a;
    this->op = o;

    this->setLabel("AdditiveExpression");
}

//Traversal
void AstAddExpr::Visit()
{
    //Visit children nodes
    if(add)
        add->Visit();

    mult->Visit();

    //Output visualization
    AST::vis.addNode(this->getUID(), this->getLabel());

    if(add)
    {
        stringstream ss;
        int tmp = Visualizer::GetNextUID();
        char c = (op == PLUS) ? '+' : '-';
        ss << c;
        AST::vis.addNode(tmp, ss.str());

        AST::vis.addEdge(this->getUID(), add->getUID());
        AST::vis.addEdge(this->getUID(), tmp);
    }

    AST::vis.addEdge(this->getUID(), mult->getUID());

    //Output 3AC
}

///////////////////////////////////////////////////////////////////////////////
// BEGIN: AstShiftExpr  ///////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//Constructor
AstShiftExpr::AstShiftExpr(AstAddExpr* a)
{
    this->add = a;
    this->shift = NULL;
    this->op = NONE;

    this->setLabel("ShiftExpression");
}

AstShiftExpr::AstShiftExpr(AstShiftExpr* s, Operator o, AstAddExpr* a)
{
    this->add = a;
    this->shift = s;
    this->op = o;

    this->setLabel("ShiftExpression");
}

//Traversal
void AstShiftExpr::Visit()
{
    //Visit children nodes
    if(shift)
        shift->Visit();

    add->Visit();

    //Output visualization
    AST::vis.addNode(this->getUID(), this->getLabel());

    if(shift)
    {
        int tmp = Visualizer::GetNextUID();
        string s = (op == LEFT_OP) ? "<<" : ">>";
        AST::vis.addNode(tmp, s);

        AST::vis.addEdge(this->getUID(), shift->getUID());
        AST::vis.addEdge(this->getUID(), tmp);
    }

    AST::vis.addEdge(this->getUID(), add->getUID());

    //Output 3AC
}


#ifndef _AST_
#define _AST_

#include <string>
#include <sstream>
#include "Visualizer.h"

class AST
{
    public:
        AST()
        {
            uid = Visualizer::GetNextUID();
            label = "LabelNotSet";
        }

        void setLabel(string l)
        {
            label = l;
        }

        int getUID() { return uid; }

        string getLabel() { return label; }

        static Visualizer vis;

	virtual void Visit(){};

    protected:
        int uid;
        string label;
};

class AstExpression : public AST
{
	
    public:
	void Visit();
};

class AstNodeStub : public AST
{
    //Place the children nodes here

    public:
        //Constructor
        AstNodeStub();

        //Traversal
        void Visit();
};
class AstTypeName : public AST
{
    //TODO implement later

    //Place the children nodes here

    public:
        //Constructor
        AstTypeName();

        //Traversal
        void Visit();
};

class AstString : public AST
{
    string val;

    public:

    AstString(string str);

    void Visit();
};

class AstConstant : public AST
{
    enum ConstType
    {
        INT,
        CHAR,
        FLOAT,
        ENUM,
    };

    ConstType type;

    int ival;
    string str;
    double dval; 

    public:
    
    AstConstant(int val);
    AstConstant(string val);
    AstConstant(double val);
    AstConstant(int val, string name);

    void Visit();
};

class AstUnaryOp : public AST
{
    //Place the children nodes here
    public:
        enum Operator
        {
            BIN_AND,
            STAR,
            PLUS,
            MINUS,
            TILDE,
            BANG
        };

    private:
        Operator op;

    public:
        //Constructor
        AstUnaryOp(Operator o);

        //Traversal
        void Visit();
};

class AstID : public AST
{
    string str;

    public:
    AstID(string s);

    void Visit();
};

class AstAssignExpr : public AST
{
    //TODO implement later

    //Place the children nodes here

    public:
        //Constructor
        AstAssignExpr();

        //Traversal
        void Visit();
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
        AstPrimaryExpr(AstID* id);
        AstPrimaryExpr(AstConstant* c);
        AstPrimaryExpr(AstString* s);
        AstPrimaryExpr(AstExpression* e);
        void Visit();
};

class AstArgExprList : public AST
{
    AstArgExprList *list;
    AstAssignExpr *expr;
    bool isLastItem;

    public:
        AstArgExprList(AstArgExprList *list, AstAssignExpr *expr);
        AstArgExprList(AstAssignExpr *expr);
        void Visit();
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
        AstPostfixExpr(AstPrimaryExpr* p);
        AstPostfixExpr(AstPostfixExpr* p, AstExpression* e);
        AstPostfixExpr(AstPostfixExpr* p);
        AstPostfixExpr(AstPostfixExpr *p, AstArgExprList *a);
        AstPostfixExpr(AstPostfixExpr *p, Operator o, AstID *i);
        AstPostfixExpr(AstPostfixExpr *p, Operator o);

        //Traversal
        void Visit();
};

class AstCastExpr;

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
        AstUnaryExpr(AstPostfixExpr *e);
        AstUnaryExpr(AstUnaryExpr* e, bool inc);
        AstUnaryExpr(AstUnaryOp* o, AstCastExpr* c);
        AstUnaryExpr(AstUnaryExpr* e);
        AstUnaryExpr(AstTypeName* t);

        //Traversal
        void Visit();
};

class AstCastExpr : public AST
{
    //Place the children nodes here
    AstUnaryExpr *uniexpr;
    AstCastExpr  *cast;
    AstTypeName  *tname;

    public:
        //Constructor
        AstCastExpr(AstUnaryExpr* u);
        AstCastExpr(AstTypeName* t, AstCastExpr* c);

        //Traversal
        void Visit();
};

class AstMultExpr : public AST
{
    //Place the children nodes here
    AstCastExpr *cast;
    AstMultExpr *mult;

    public:
        enum Operator
        {
            NONE,
            STAR,
            DIV, 
            MOD
        } op;

        //Constructor
        AstMultExpr(AstCastExpr* c);
        AstMultExpr(AstMultExpr* m, Operator o, AstCastExpr* c);

        //Traversal
        void Visit();
};

class AstAddExpr : public AST
{
    //Place the children nodes here
    AstMultExpr *mult;
    AstAddExpr *add;

    public:
        enum Operator
        {
            NONE,
            PLUS,
            MINUS
        } op;

        //Constructor
        AstAddExpr(AstMultExpr* m);
        AstAddExpr(AstAddExpr* a, Operator o, AstMultExpr* m);

        //Traversal
        void Visit();
};

class AstShiftExpr : public AST
{
    //Place the children nodes here
    AstAddExpr *add;
    AstShiftExpr *shift;

    public:
        enum Operator
        {
            NONE,
            LEFT_OP,
            RIGHT_OP
        } op;

        //Constructor
        AstShiftExpr(AstAddExpr* a);
        AstShiftExpr(AstShiftExpr* s, Operator o, AstAddExpr* a);

        //Traversal
        void Visit();
};

class AstRelExpr : public AST
{
    //Place the children nodes here
    AstShiftExpr *shift;
    AstRelExpr   *rel;

    public:
        enum Operator
        {
            NONE,
            LT_OP,
            GT_OP,
            LE_OP,
            GE_OP
        } op;

        //Constructor
        AstRelExpr(AstShiftExpr* s);
        AstRelExpr(AstRelExpr* r, Operator o, AstShiftExpr* s);

        //Traversal
        void Visit();
};

class AstEqExpr : public AST
{
    //Place the children nodes here
    AstRelExpr *rel;
    AstEqExpr  *eq;

    public:
        enum Operator
        {
            NONE,
            EQ_OP,
            NE_OP
        } op;

        //Constructor
        AstEqExpr(AstRelExpr* r);
        AstEqExpr(AstEqExpr* e, Operator o, AstRelExpr* r);

        //Traversal
        void Visit();
};

class AstAndExpr : public AST
{
    AstEqExpr  *eq;
    AstAndExpr *a;

    public:
        AstAndExpr(AstEqExpr* e);
        AstAndExpr(AstAndExpr* a, AstEqExpr* e);
        void Visit();
};























#endif 

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

class AstExpression;

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

class AstAssignExpr;

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

class AstXORExpr : public AST
{
    AstAndExpr *a;
    AstXORExpr *x;

    public:
        AstXORExpr(AstAndExpr* a);
        AstXORExpr(AstXORExpr* x, AstAndExpr* a);
        void Visit();
};

class AstORExpr : public AST
{
    AstXORExpr *x;
    AstORExpr *o;

    public:
        AstORExpr(AstXORExpr* x);
        AstORExpr(AstORExpr* o, AstXORExpr* x);
        void Visit();
};

class AstLogicAndExpr : public AST
{
    AstORExpr *o;
    AstLogicAndExpr *a;

    public:
        AstLogicAndExpr(AstORExpr* o);
        AstLogicAndExpr(AstLogicAndExpr* a, AstORExpr* o);
        void Visit();
};

class AstLogicOrExpr : public AST
{
    AstLogicAndExpr *a;
    AstLogicOrExpr *o;

    public:
        AstLogicOrExpr(AstLogicAndExpr* a);
        AstLogicOrExpr(AstLogicOrExpr* o, AstLogicAndExpr* a);
        void Visit();
};

class AstConditionalExpr : public AST
{
    AstLogicOrExpr* o;
    AstExpression* e;
    AstConditionalExpr* ce;

    public:

        AstConditionalExpr(AstLogicOrExpr* o);
        AstConditionalExpr(AstLogicOrExpr* o, AstExpression* e, AstConditionalExpr* ce);
        void Visit();
};

class AstConstantExpr : public AST
{
    AstConditionalExpr *expr;

    public:
        AstConstantExpr(AstConditionalExpr *e);
        void Visit();
};

class AstAssignOp : public AST
{
    //Place the children nodes here
    public:
        enum Operator
        {
            EQ,
            MUL_ASSIGN,
            DIV_ASSIGN,
            MOD_ASSIGN,
            ADD_ASSIGN,
            SUB_ASSIGN,
            LEFT_ASSIGN,
            RIGHT_ASSIGN,
            AND_ASSIGN,
            XOR_ASSIGN,
            OR_ASSIGN
        };

    private:
        Operator op;

    public:
        //Constructor
        AstAssignOp(Operator o);

        //Traversal
        void Visit();
};

class AstAssignExpr : public AST
{
    AstConditionalExpr* cond;
    AstUnaryExpr* uni;
    AstAssignOp* op;
    AstAssignExpr* expr;

    public:
        AstAssignExpr(AstConditionalExpr* c);
        AstAssignExpr(AstUnaryExpr* u, AstAssignOp* a, AstAssignExpr* e);
        void Visit();
};

class AstExpression : public AST
{
    AstAssignExpr* ass;
    AstExpression* expr;

    public:
        AstExpression(AstAssignExpr* a);
        AstExpression(AstExpression* e, AstAssignExpr* a);
	void Visit();
};

class AstReturn : public AST
{
    AstExpression *expr;

    public:    
        AstReturn(AstExpression *r);
        AstReturn();
        void Visit();
};

class AstContinue : public AST 
{
    public:
        AstContinue();
        void Visit();	
};

class AstBreak : public AST 
{	
    public:
        AstBreak();
        void Visit();	
};

class AstGoto : public AST
{
    public:
        AstGoto();
        void Visit();	
};

class AstJump : public AST
{
    AstGoto* go;
    AstID* id;
    AstContinue* cont;
    AstBreak* br;
    AstReturn* ret;
    AstExpression* expr;

    public:
        enum Type
        {
            GOTO,
            CONTINUE,
            BREAK,
            EMPTY_RETURN,
            RETURN
        } t;

        AstJump(AstGoto* g, AstID* i);
        AstJump(AstContinue* c);
        AstJump(AstBreak* b);
        AstJump(AstReturn* r);
        AstJump(AstReturn* r, AstExpression* e);
        void Visit();
};

class AstStatement;

class AstDoWhile : public AST
{
    AstExpression *test;
    AstStatement *statement;

    public:
        AstDoWhile( AstStatement *s, AstExpression *t );
        void Visit();
};

class AstWhile : public AST
{
    AstExpression *test;
    AstStatement *statement; 

    public:
        AstWhile( AstExpression *test, AstStatement *statement );
        void Visit();
};

class AstFor : public AST
{
    AstExpression *init;
    AstExpression *test;
    AstExpression *increment;
    AstStatement *statement; 

    public:
        AstFor(AstExpression *init , AstExpression *test , AstExpression *increment , AstStatement *statement);
        void Visit();
};

class AstIteration : public AST
{
    AstDoWhile* dwl;
    AstWhile* wl;
    AstFor* fr;

    public:
        enum Type
        {
            DOWHILE,
            WHILE,
            FOR
        } t;

        AstIteration(AstDoWhile* d);
        AstIteration(AstWhile* w);
        AstIteration(AstFor* f);
        void Visit();
};

class AstSwitch : public AST
{
    AstExpression* expr; 
    AstStatement* stmt;

    public:
        AstSwitch(AstExpression* e, AstStatement* s);
        void Visit();
};

class AstIfElse : public AST 
{
    AstExpression *test ; 
    AstStatement *statement;
    AstStatement *elseStatement;
    
    public:
        AstIfElse( AstExpression *test , AstStatement *statement , AstStatement *elseStatement );
        void Visit();
};

class AstSelection : public AST
{
    AstSwitch* swtch;
    AstIfElse* ifelse;

    public:
        enum Type
        {
            SWITCH,
            IFELSE
        } t;

        AstSelection(AstSwitch* s);
        AstSelection(AstIfElse* ie);
        void Visit();
};

class AstStatementList : public AST
{
    AstStatement *stmt; 
    AstStatementList *list;

    public:
        AstStatementList(AstStatement *s);
        AstStatementList(AstStatementList* l, AstStatement *s);
        void Visit();
};

class AstDeclarationList;

class AstCompoundStmt : public AST
{
    AstStatementList* stmtList;
    AstDeclarationList* declList;

    public:
        AstCompoundStmt(AstDeclarationList* d, AstStatementList* s);
        void Visit();
};

class AstExprStmt : public AST
{
    AstExpression* expr;

    public:
        AstExprStmt(AstExpression* e);
        void Visit();
};

class AstLabeledStmt : public AST
{
    AstID *id;
    AstStatement *stmt;
    AstConstantExpr *constExpr;

    public:
        enum Type
        {
            NO_CASE,
            CASE,
            DEFAULT
        } t;

        AstLabeledStmt(AstID* i, AstStatement* s);
        AstLabeledStmt(AstConstantExpr* c, AstStatement* s);
        AstLabeledStmt(AstStatement* s);
        void Visit();
};

class AstStatement : public AST 
{
    AstLabeledStmt  *lbl;
    AstCompoundStmt *cmp;
    AstExprStmt     *expr;
    AstSelection    *slct;
    AstIteration    *iter;
    AstJump         *jump;

    public:
        enum Type
        {
            LABELED,
            COMPOUND,
            EXPR,
            SELECT,
            ITER,
            JUMP
        } t;

        AstStatement(AstLabeledStmt* l);
        AstStatement(AstCompoundStmt* c);
        AstStatement(AstExprStmt* e);
        AstStatement(AstSelection* s);
        AstStatement(AstIteration* i);
        AstStatement(AstJump* j);

        void Visit();
};




//TODO - Implement the classes below here later
class AstDeclarationList : public AST 
{
    public:
        void Visit(){}
};










#endif 

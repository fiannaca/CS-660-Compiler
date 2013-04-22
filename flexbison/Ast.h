#ifndef _AST_
#define _AST_

#include <string>
#include <sstream>
#include "Visualizer.h"
#include "Type.h"
#include "TAC_Generator.h"

class AST;
extern void VisVist(int total , ... );
extern void VisAddIntNode ( AST *parentAst , int number );
extern void VisAddStringNode(  AST *parentASt , string &node); 

/**
 * Abstract syntax tree node type
 */
class AST
{
    public:
        /**
         * AST default constructor. This default constructor ensures that every
         * node has a label and a unique identifier (used for visualizing the 
         * tree)
         */
        AST()
        {
            uid = Visualizer::GetNextUID();
            label = "LabelNotSet";
            needsCast = false;
            convType = NONE;
            operandToCast = 1;
            isConv = true;
            returnLabel = "";
        }

        /**
         * Sets the label for the node.
         *
         * @param l The label string
         */
        void setLabel(string l)
        {
            label = l;
        }

        /**
         * Gets the node's unique ID.
         *
         * @return The unique id
         */
        int getUID() { return uid; }

        /**
         * Gets the node's label.
         *
         * @return The label
         */
        string getLabel() { return label; }

        /**
         * Static visualizer instance for generating the visualization of the 
         * AST.
         */
        static Visualizer vis;

        /**
         * This function is responsible for tree traversals. This function will
         * call the Visit functions of each of it's children nodes, call the 
         * visualization code for itself, and output any 3AC that can be 
         * generated at the current node.
         */
	    virtual void Visit(){};
	    
        /**
         * Three address code generator.
         */
        static TAC_Generator tacGen;
        
        bool needsCast; /**< This indicates if cast 3AC needs to be output, and is only relevant for expressions */
        bool isConv; /**< Indicates is a conversion is possible */
        CONVERSIONTYPE convType; /**< If needsCast is true, then this indicates what the cast should be */
        int operandToCast; /**< This indicates if the first or second operand should be the one that is cast */
        string currentTemp;  
        string returnLabel; /**< This is for storing the string id of any temporary result register that may be created during 3AC generation */
        list<string> tempStack; /* stack to hold the temporay variables used */    
        string lastID;   
    protected:
        int uid; /**< The unique id */
        string label; /**< The label to be printed in the visualization */
};

class AstSpeciQualList;
class AstAbstractDecl;

class AstTypeName : public AST
{
    //TODO implement later

    //Place the children nodes here
    AstSpeciQualList *list;
    AstAbstractDecl *decl;
public:
        //Constructor
        AstTypeName()
        {
			this->setLabel("TypeName");
		}
		
        AstTypeName(AstSpeciQualList *list , AstAbstractDecl *decl )
        {
			this->list = list ;
			this->decl = decl;
			this->setLabel("TypeName"); 
		}

        //Traversal
        void Visit();
      
       
};

class AstString : public AST
{
    string val;

    public:

    AstString(string str, Type* t);
    
    Type* type;

    void Visit();
};

class AstConstant : public AST
{
    

public:
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

    
    
    AstConstant(int val);
    AstConstant(string val);
    AstConstant(double val);
    AstConstant(int val, string name, Type* t);

    Type* etype;

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
    
public:
    string str;

   
    AstID(string s, Type* t);
    
    Type* type;

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

        Type* etype;
    
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

        enum ExprType
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
        ExprType t;    

    public:

        //Constructor
        AstPostfixExpr(AstPrimaryExpr* p);
        AstPostfixExpr(AstPostfixExpr* p, AstExpression* e);
        AstPostfixExpr(AstPostfixExpr* p);
        AstPostfixExpr(AstPostfixExpr *p, AstArgExprList *a);
        AstPostfixExpr(AstPostfixExpr *p, Operator o, AstID *i);
        AstPostfixExpr(AstPostfixExpr *p, Operator o);
        
        Type* type;

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
        enum ExprType
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
        
        Type* type;

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
        
        Type* type;

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
        
        Type* type;

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
        
        Type* type;

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
        
        Type* type;

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
        
        Type* type;

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
        
        Type* type;

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
        
        Type* type;
        
        void Visit();
};

class AstXORExpr : public AST
{
    AstAndExpr *a;
    AstXORExpr *x;

    public:
        AstXORExpr(AstAndExpr* a);
        AstXORExpr(AstXORExpr* x, AstAndExpr* a);
        
        Type* type;
        
        void Visit();
};

class AstORExpr : public AST
{
    AstXORExpr *x;
    AstORExpr *o;

    public:
        AstORExpr(AstXORExpr* x);
        AstORExpr(AstORExpr* o, AstXORExpr* x);
        
        Type* type;
        
        void Visit();
};

class AstLogicAndExpr : public AST
{
    AstORExpr *o;
    AstLogicAndExpr *a;

    public:
        AstLogicAndExpr(AstORExpr* o);
        AstLogicAndExpr(AstLogicAndExpr* a, AstORExpr* o);
        
        Type* type;
        
        void Visit();
};

class AstLogicOrExpr : public AST
{
    AstLogicAndExpr *a;
    AstLogicOrExpr *o;

    public:
        AstLogicOrExpr(AstLogicAndExpr* a);
        AstLogicOrExpr(AstLogicOrExpr* o, AstLogicAndExpr* a);
        
        Type* type;
        
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
        
        Type* type;
        
        void Visit();
};

class AstConstantExpr : public AST
{
    AstConditionalExpr *expr;

    public:
        AstConstantExpr(AstConditionalExpr *e);
        
        Type* type;
        
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

   
        

    public:
        Operator op;
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

        Type* type;
    
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


class AstDeclarationList;
class AstStatementList;
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




//TODO - Implement cthe classes below here later
class AstDecl;
class AstPointer;
class AstIDList;
class AstParamList;
class AstInitializer;
class AstInitList;
class AstTypeQualList;
class AstParamDec;
class AstDecSpeci;
class AstDeclarator;
class AstAbstractDecl;

class AstExternDec;
class AstTrans;
class EnumSpecifier;


class AstStructDeclList;
class AstStructUniSpeci: public AST 
{
	
	string structOrUnion; 
	AstID  *structName;
	AstStructDeclList *sdlist; 
	public:
		AstStructUniSpeci(string structOrUnion ,  AstID  *sName  , AstStructDeclList *sdlist)
		{
		    this->structOrUnion = structOrUnion ; 
	            this->structName = sName;
		    this->sdlist = sdlist; 
		    this->setLabel("AstStructUniSpeci");

		}
		void Visit() 
		{
			VisVist(2,structName,sdlist);
                         
		}
	
};
class AstStructDecl;


class AstStructDeclarator;
class AstStructDeclatorList : public AST
{
	AstStructDeclarator *sdecl; 
	AstStructDeclList *stdlist;
public:
	AstStructDeclatorList( AstStructDeclarator *sdecl , AstStructDeclList *stdlist)
	{
		this->sdecl= sdecl ;
		this->stdlist = stdlist; 
	        this->setLabel("AstDeclaratorList");
}
	void Visit()
	{
		VisVist(2 ,this ,  stdlist , sdecl );

	} 
	
};
class AstDeclarator;
class AstStructDeclarator : public AST
{
	AstDeclarator *decl ;
	AstExpression *exp ;
public:
    AstStructDeclarator ( AstDeclarator *decl , AstExpression *exp )
    {
		this->decl = decl;
		this->exp = exp;
	        this->setLabel("AstStructDeclarator");
}
	void Visit()
	{
	    VisVist(2 ,this,  exp , decl );

	}
};


class AstPointer : public AST
{
	 AstPointer *pointer;
	 AstTypeQualList *list;
	  
public:
	AstPointer(AstPointer *pointer , AstTypeQualList *list  )
	{
		this->pointer = pointer;
		this->list= list ; 
		this->setLabel("AstPointer");

	}
	void Visit()
	{
		VisVist(2 ,this , pointer , list );

	}
	
} ; 

class AstParamList : public AST
{
	
    AstParamDec *dec;
	AstParamList *plist;
public:
	AstParamList( AstParamDec *dec , AstParamList *plist)
	{
		this->dec = dec; 
		this->plist = plist ;
                this->setLabel("AstParamList");
  
	}
	void Visit()
	{
		VisVist(2 , this , dec , plist );

	} 
	
};
class AstParamDec : public AST
{
	AstDecSpeci *speci;
	AstDeclarator *declarator; 
	AstAbstractDecl *adecl; 
public:
    AstParamDec (AstDecSpeci *speci ,AstDeclarator *declarator , AstAbstractDecl *adecl )
    {
    	this->speci = speci;
    	this->declarator = declarator; 
    	this->adecl = adecl;
        this->setLabel("AstParamDec");
  
    }
	void Visit()
	{
	   VisVist(3 , this , speci , declarator , adecl );
	
	}
	
}; 
class AstInitializer;
class AstInitList;

class AstInitList : public AST 
{


	AstInitializer *intializer;
	AstInitList *list;
public:
	AstInitList( AstInitializer *intializer  , AstInitList *list)
	{
		this->intializer = intializer ; 
		this->list =  list ; 
                this->setLabel("AstInitList");

	}
	void Visit()
	{
		VisVist(2 ,this, intializer , list );

	} 
	
};

class AstIDList : public AST
{
	
    AstID  *id;
	AstIDList *idlist;
public:
	AstIDList( AstID *id , AstIDList *idlist)
	{
		this->id = id; 
		this->idlist = idlist ;
                this->setLabel("AstIDList");
  
	}
	void Visit()
	{
		VisVist(2 ,this, id , idlist );

	} 
	
};
class AstCompound;
class AstDeclList;
class AstDecl;

class AstFuncDef: public AST 
{
	AstDeclarator *decl;
	AstCompound *comp;
	AstDeclList *dlist;
	AstDecSpeci *speci ; 
	AstDecl *dec; 
	public:
		AstFuncDef( AstDeclarator *decl , AstCompound *comp , AstDeclList *dlist, AstDecSpeci *speci)
		{
			this->decl = decl ;
			this->comp = comp;
			this->dlist = dlist;
			this->speci = speci;
                        this->setLabel("AstFuncDef");
  
		}
		void Visit() 
		{
			VisVist(4 , this,decl ,comp , dlist,speci);

		}
	
};

class AstDeclarationList : public AST 
{
    public:
        void Visit(){}
};

/*
class AstEnumSpeci : public AST
{
	
	public:
	AstEnumSpeci()
	{
              this->setLabel("EnumSpeci");
		
	}
	void Visit() 
	{
	
		
	}
	
};
*/
class AstStructUniSpeci;
class AstTypeSpeci: public AST 
{
	
	string stypeName;
	AstStructUniSpeci *stspeci ; 
	EnumSpecifier *espci;
	
	public:
		AstTypeSpeci(string stypeName , AstStructUniSpeci *stspeci , EnumSpecifier *espci)
		{
		    this->stspeci = stspeci;
		    this->espci = espci; 
		    this->stypeName = stypeName; 
		    this->setLabel("AstTypeSpeci");

		}
		void Visit() 
		{
			VisVist(2,this,stspeci,espci);
                        VisAddStringNode(this , stypeName);
		}
	
};

class AstTypeQualList : public AST
{
	string type_qual; 
	AstTypeQualList *list;
public:
	AstTypeQualList( string type_qual , AstTypeQualList *list)
	{
		this->type_qual= type_qual ;
		this->list = list;
                this->setLabel("AstTypeQualList");
 
	}
	void Visit()
	{
	      VisVist(1,this,list);
              VisAddStringNode(this,type_qual);	
	} 
	
};
class AstExternDec;
class AstTrans;

class AstTrans: public AST 
{
	AstTrans *trans;
	AstExternDec *dec; 
	public:
		AstTrans( AstTrans *trans ,AstExternDec *dec)
		{
			this->trans = trans;
			this->dec= dec;
                        this->setLabel("AstTrans");
  
		}
		void Visit() 
		{
			VisVist(2 ,this, trans , dec );

		}
	
};
class AstStructDeclList;
class AstStructDecl;
class AstStructDeclList : public AST
{
	AstStructDecl *sdecl; 
	AstStructDeclList *stdlist;
public:
	AstStructDeclList( AstStructDecl *sdecl , AstStructDeclList *stdlist)
	{
		this->sdecl= sdecl ;
		this->stdlist = stdlist;
                this->setLabel("AstStructDeclList");
 
	}
	void Visit()
	{
		VisVist(2 ,this, stdlist , sdecl );

	} 
	
};

class AstDeclarator;

class AstStatementList : public AST
{
    AstStatement *stmt; 
    AstStatementList *list;

    public:
        AstStatementList(AstStatement *s);
        AstStatementList(AstStatementList* l, AstStatement *s);
        void Visit();
};

class AstTypeParamList;
class AstDirectDecl : public AST
{
	 int type; 
	 AstID *id ;
	 AstDirectDecl *ddecl;
	 AstExpression *exp;
	 AstDeclarator *decl;
	 AstTypeParamList *pList;
	 AstIDList *idList; 
public:
	AstDirectDecl(AstID *id ,  AstDirectDecl *ddecl , AstExpression *exp , AstDeclarator *decl , AstTypeParamList *plist ,AstIDList *idList, int type  )
	{
		this->id = id ; 
		this->ddecl = ddecl;
		this->decl = decl;
		this->exp = exp ;
		this->pList= plist;
		this->idList = idList; 
		this->type = type ;
                this->setLabel("AstDirectDecl");

		
	}
	void Visit()
	{
	   VisVist(6,this,id,ddecl,decl,exp,pList,idList);	
           VisAddIntNode(this,type); 
	}
	
} ; 
class AstTypeSpeci;
class AstDecSpeci: public AST 
{
	
	string storage_class;
	string type_qual; 
	AstDecSpeci *speci; 
	AstTypeSpeci *typeSpeci; 
	public:
		AstDecSpeci(string str_class , string typeq , AstDecSpeci *speci , AstTypeSpeci *typeSpeci)
		{
			this->storage_class =  str_class;
			this->type_qual = typeq; 
			this->speci  = speci ; 
			this->typeSpeci = typeSpeci;
                        this->setLabel("AstDecSpeci");
  
		}
		void Visit() 
		{
		   VisVist(2,this , speci,typeSpeci);	
                   VisAddStringNode(this,storage_class);
                   VisAddStringNode(this,type_qual);
		}
	
};
class AstDeclList: public AST 
{
	
	AstDecl *decl ; 
	AstDeclList *list; 
	public:
		AstDeclList( AstDeclList *list , AstDecl *decl)
		{
			this->list  = list ; 
			this->decl = decl;
                        this->setLabel("AstDeclList");

		}
		void Visit() 
		{
			VisVist(2 ,this , list , decl );

			   
		}
	
};


class AstInitSpecList; 
class AstDecl: public AST 
{
	
	AstDecSpeci *speci ; 
	AstInitSpecList *list; 
	public:
		AstDecl( AstDecSpeci *speci , AstInitSpecList *list)
		{
			this->list  = list ; 
			this->speci = speci;
                        this->setLabel("AstDecl");
   
		}
		void Visit() 
		{
		    VisVist(2 ,this , speci , list);
	
		}
	
};

class AstDirectAbsDecl;
class AstAbstractDecl : public AST
{
	
	AstPointer *pointer;
	AstDirectAbsDecl *dec; 
public:
	AstAbstractDecl(  AstPointer *pointer , AstDirectAbsDecl *dec)
	{
		this->pointer = pointer;
		this->dec = dec; 
                this->setLabel("AstAbstractDecl");

	} 
	void Visit()
	{
		VisVist(2 , pointer , dec );

	}
	
};
class AstTypeParamList : public AST 
{
	 int type ; 
	 AstParamList *list;
public:
     AstTypeParamList( int type , AstParamList *list )
     {
	    this->type =type;
	    this->list = list;
	    this->setLabel("AstTypeParamlList");
 } 
	 void Visit()
	 {
               VisVist(1,this,list);	 
               VisAddIntNode(this,type);
	 }
	
};

class  AstDirectAbsDecl : public AST
{
	int type;
	AstAbstractDecl *decl;
	AstExpression *exp;
	AstDirectAbsDecl *dabsdecl;
	AstTypeParamList *pList;
public:
    AstDirectAbsDecl(int type , AstAbstractDecl *decl , AstExpression *exp ,  AstDirectAbsDecl *dabsdecl , AstTypeParamList *pList  )
    {
		this->decl =  decl ;
		this->exp = exp ;
		this->dabsdecl = dabsdecl;
		this->pList = pList ;
	        this->setLabel("AstDirectAbsDecl");

	}
	void Visit()
	{
	 // VisVist(2 , pointer , decl );
            VisVist(4,this,decl,exp,dabsdecl,pList); 
            VisAddIntNode(this, type);   
	}
	
};
class AstInitDeclarator; 
class AstInitDeclList: public AST 
{
	AstInitDeclarator *decl ;
	AstInitDeclList *list;
public:
    AstInitDeclList( AstInitDeclarator *decl ,AstInitDeclList *list)
    {
		this->decl = decl;
		this->list = list; 
                this->setLabel("AstInitDeclList");

	}
	void Visit()
	{
		VisVist(2 , this , list , decl );

	}
};
class AstInitDeclarator : public AST
{
	 AstDeclarator *decl;
	 AstInitializer *init;
public:
     AstInitDeclarator( AstDeclarator *decl , AstInitializer *init )
     {
	     this->decl = decl;
	     this->init = init;	
             this->setLabel("AstInitDeclarator");
 
	 }
     void Visit()
     {
		 VisVist(2 ,this, init , decl );

	 }
};
class AstInitializer : public AST 
{
	AstAssignExpr *expr ;
	AstInitList *list;
	int type; 
public:
    AstInitializer ( AstAssignExpr *expr , AstInitList *list ,int type)
    {
	   this->expr = expr ;
	   this->list = list ; 
	   this->type =   type ; 
           this->setLabel("AstInitializer");
	
	}
	void Visit()
	{
		VisVist(2, this , expr,list);
                VisAddIntNode(this,type);    
	}
	
};
class AstEnumerator : public AST 
{
    AstID *id ;
    AstExpression *exp;
public:
    AstEnumerator(AstID *id , AstExpression *exp )
    {
		this->id = id ;
		this->exp = exp; 
		this->setLabel("AstEnumerator");

	}
	void Visit()
	{
		VisVist(2 ,this, id , exp );

	}
};
class AstEnumList : public AST 
{
    AstEnumerator *en;
    AstEnumList *list;
public:
    AstEnumList(  AstEnumerator *en ,AstEnumList *list )
    {
	    this->en = en ;
	    this->list =list;
            this->setLabel("AstEnumList");
  
	}  	
    void Visit()
    {
	VisVist(2 ,this , en , list );
	
	}

};
class EnumSpecifier : public AST 
{
	AstID *id ;
	AstEnumList *list;
public:
    EnumSpecifier( AstID *id , AstEnumList *list )
    {
		this->id = id;
		this->list = list;
                this->setLabel("EnumSpecifier");
 
	}
	void Visit()
	{
                VisVist(2 ,this,  id , list );

	}
};

class AstSpeciQualList: public AST
{
	 AstTypeSpeci *typespeci;
	 string qual;
	 AstSpeciQualList *list;
public:
     AstSpeciQualList( AstTypeSpeci *typespeci , string qual , AstSpeciQualList *list )
     {
	     this->typespeci = typespeci ;
	     this->qual      = qual;
	     this->list      = list; 
             this->setLabel("AstSpeciQualList");


	 } 
	 void Visit()
	 {
	        // VisVist(2 , pointer , decl );
               VisVist(2, this , typespeci,list);   
               VisAddStringNode(this,qual);  
	 }
};
class AstStructDecl : public AST 
{
	 AstSpeciQualList *list ;
	 AstStructDeclList *declList; 
public:
     AstStructDecl ( AstSpeciQualList *list , AstStructDeclList *declList )
     {
	       this->list = list;
	       this->declList = declList;
               this->setLabel("AstStructDecl");
 
	 }
	 void Visit()
	 {
	     VisVist(2 ,this,  list , declList );

	 }
	
};
class 	AstDeclarator : public AST 
{
	AstPointer *pointer;
	AstDirectDecl *decl;
public:
    AstDeclarator(AstPointer *pointer , AstDirectDecl *decl )
	{
		this->pointer = pointer ;
		this->decl = decl ; 
	        this->setLabel("AstDeclarator");
	
	}  
	void Visit()
	{
		VisVist(2 ,this,  pointer , decl );

	}
	
	
};
#endif 

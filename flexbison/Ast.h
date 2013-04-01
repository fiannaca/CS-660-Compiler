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
class AstStatement:public AST 
{
	
public:
	void Visit()
	{
		
	}
};

class AstGoto : public AstStatement
{
     AstID* label; 	
public:
    AstGoto(AstID* label)
    {
	   this->label = label ;
	}
	void Visit()
	{
		
	}
};

class AstWhile : public AstStatement
{
    AstExpression *test;
    AstStatement *statement; 

    public:
    
    AstWhile( AstExpression *test, AstStatement *statement )
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
class AstEnumSpeci : public AST
{
	
	public:
	AstEnumSpeci()
	{
		
	}
	void Visit() 
	{
	
		
	}
	
};

class AstStructUniSpeci;
class AstTypeSpeci: public AST 
{
	
	string stypeName;
	AstStructUniSpeci *stspeci ; 
	AstEnumSpeci *espci;
	
	public:
		AstTypeSpeci(string stypeName , AstStructUniSpeci *stspeci , AstEnumSpeci *espci)
		{
		    this->stspeci = stspeci;
		    this->espci = espci; 
		    this->stypeName = stypeName; 
		    
		}
		void Visit() 
		{
			
		}
	
};

class AstTypeQualList : public AstStatement 
{
	string type_qual; 
	AstTypeQualList *list;
public:
	AstTypeQualList( string type_qual , AstTypeQualList *list)
	{
		this->type_qual= type_qual ;
		this->list = list; 
	}
	void Visit()
	{
		
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
		}
		void Visit() 
		{
			
		}
	
};
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
		    
		}
		void Visit() 
		{
			
		}
	
};
class AstStructDecl;
class AstStructDeclList : public AstStatement 
{
	AstStructDecl *sdecl; 
	AstStructDeclList *stdlist;
public:
	AstStructDeclList( AstStructDecl *sdecl , AstStructDeclList *stdlist)
	{
		this->sdecl= sdecl ;
		this->stdlist = stdlist; 
	}
	void Visit()
	{
		
	} 
	
};

class AstStatementList : public AstStatement 
{
	
	AstStatement *stmt;
	AstStatementList *list; 
public:
	AstStatementList( AstStatement *stmt , AstStatementList *list)
	{
		this->stmt = stmt;
		this->list= list ;
	}
	void Visit()
	{
		
	} 
	
};

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
		/*
        AST::vis.addNode(this->getUID(), this->getLabel());
        AST::vis.addEdge(this->getUID(), returnExpression->getLabel());
        */ 
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
		
	}
	void Visit()
	{
		
	}
	
} ; 
class AstParamDec;
class AstParamList;
class AstParamList : public AstStatement 
{
	
    AstParamDec *dec;
	AstParamList *plist;
public:
	AstParamList( AstParamDec *dec , AstParamList *plist)
	{
		this->dec = dec; 
		this->plist = plist ; 
	}
	void Visit()
	{
		
	} 
	
};
class AstDecSpeci;
class AstDeclarator;
class AstAbstractDecl;
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
    }
	void Visit()
	{
		
	}
	
}; 

class AstLabel: AstStatement 
{
    AstID* labelName;
    AstStatement *statement;

    public:
    AstLabel ( AstID* labelName , AstStatement *stmt)
    {
        this->labelName = labelName;
        this->statement = stmt;

        this->setLabel("LabelStatement"); 
    }

    void Visit() 
    {
        AST::vis.addNode(this->getUID(), this->getLabel());
        AST::vis.addEdge(this->getUID(), statement->getUID());
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
	}
	void Visit()
	{
		
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
	}
	void Visit()
	{
		
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
		}
		void Visit() 
		{
			
		}
	
};

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

class AstSwitch : public  AstStatement
{
    AstExpression *expr;
    AstStatement *smmt;
 public:
    AstSwitch( AstExpression *expr , AstStatement *smmt )
    {
	    this->expr = expr ;
	    this->smmt = smmt;
	}	

};
class AstExternDec: public AST 
{
	AstFuncDef *def;
	AstDecl *dec; 
	public:
		AstExternDec( AstFuncDef  *def ,AstDecl *dec)
		{
			this->def = def;
			this->dec = dec ;
		}
		void Visit() 
		{
			
		}
	
};
class AstEmpty: AstStatement 
{
	
	public:
		void Visit() 
		{
			
		}
	
};
class AstDoWhile : public AstStatement
{
	AstExpression *test;
	AstStatement *statement; 
public:
    AstDoWhile( AstExpression *test, AstStatement *statement )
    {
    	this->statement = statement;
    	this->test = test; 
    }
	void Visit()
	{
		
	}
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
	AstDirectDecl(AstID *id ,  AstDirectDecl *ddecl , AstExpression *exp , AstDeclarator *decl , AstTypeParamList *plist ,AstIDList *idList  )
	{
		this->id = id ; 
		this->ddecl = ddecl;
		this->decl = decl;
		this->exp = exp ;
		this->pList= plist;
		this->idList = idList; 
		
	}
	void Visit()
	{
		
	}
	
} ; 
class AstDefault : public AstStatement
{

	
	AstStatement *statement ; 
public:
	AstDefault(  AstStatement *stmt)
	{
	
		this->statement = stmt;
	}
	void Visit()
	{
		
	}
	
};
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
		}
		void Visit() 
		{
			
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
		}
		void Visit() 
		{
			
			   
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
		}
		void Visit() 
		{
			
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
		
	}  
	void Visit()
	{
		
	}
	
	
};
class AstBreak:public AstStatement 
{
	
	public:
		void Visit() 
		{
			
		}
	
};
class AstContinue:public AstStatement 
{
	
	public:
		void Visit() 
		{
			
		}
	
};
class AstCompound : public AstStatement 
{
	AstDeclList *dlist;
	AstStatementList *slist; 
public:
	AstCompound( AstDeclList *dlist , AstStatementList *slist)
	{
		this->dlist  = dlist;
		this->slist = slist; 
	}
	void Visit()
	{
		
	} 
	
};

class AstCase : public AstStatement
{
	AstExpression *expression;
	AstStatement *statement ; 
public:
	AstCase( AstExpression *exp , AstStatement *stmt)
	{
		this->expression = exp;
		this->statement = stmt;
	}
	void Visit()
	{
		
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
	} 
	void Visit()
	{
		
	}
	
};
class AstTypeParamList
{
	 int type ; 
	 AstParamList *list;
public:
     AstTypeParamList( int type , AstParamList *list )
     {
	    this->type =type;
	    this->list = list;
	 } 
	 void Visit()
	 {
	 
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
	
	}
	void Visit()
	{
		
	}
	
};
class AstSpeciQualList: public AST
{
	 
	
};

#endif 

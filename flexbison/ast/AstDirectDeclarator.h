#ifndef _AST_DIRECT_H_
#define _AST_DIRECT_H_
class AstDirectDecl : public AST
{
	 int type; 
	 AstID *id ;
	 AstDirectDecl *decl;
	 AstExpression *exp;
	 AstDeclarator *decl;
	 AstTypeParamList *pList;
	 AstIDList *idList; 
public:
	AstDirectDecl(AstID *id ,  AstDirectDecl *decl , AstExpression *exp , AstDeclarator *decl , AstTypeParamList *plist ,AstIDList *idList  )
	{
		this->id = id ; 
		this->decl = decl;;
		this->exp = exp ;
		this->pList= plist;
		this->idList = idList; 
		
	}
	void Visit()
	{
		
	}
	
} ; 


#endif 

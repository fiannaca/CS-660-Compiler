#ifndef  _AST_DECLARATOR_H_
#define _AST_DECLARATOR_H_

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

#endif 

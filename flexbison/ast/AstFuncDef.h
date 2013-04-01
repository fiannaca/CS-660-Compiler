#ifndef _AST_FUNCDEC_
#define _AST_FUNCDEC_
#include "Ast.h"
#include "AstDeclList.h"
class AstFuncDef: public AST 
{
	AstDeclarator *decl;
	AstCompound *comp;
	AstDeclList *dlist;
	AstDecSpeci *speci ; 
	AstDecl *dec; 
	public:
		AstFuncDef( AstDeclator *decl , AstComput *comp , AstDeclList *dlist, AstSpeci *speci])
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
#endif 

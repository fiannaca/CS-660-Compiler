#ifndef _AST_DECL_
#define _AST_DECL_
#include "Ast.h"

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
#endif 

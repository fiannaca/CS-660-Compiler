#ifndef _AST_DECLIST_
#define _AST_DECLIST_
#include "Ast.h"
class AstDeclList: public AST 
{
	
	AstDecSpeci *speci ; 
	AstDeclList *list; 
	public:
		AstDeclList( AstDeclList *list , AstSpeci *speci)
		{
			this->list  = list ; 
			this->speci = speci; 
		}
		void Visit() 
		{
			
			   
		}
	
};
#endif 

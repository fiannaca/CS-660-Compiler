#ifndef _AST_DECLSPEC_
#define _AST_DECLSPEC_
#include "Ast.h"
class AstDecSpeci: public AST 
{
	
	string storage_class;
	string type_qual; 
	AstDecSpeci *speci; 
	AstTypeSpeci *typeSpeci; 
	public:
		AstDecSpeci(string str_class , string typeq , DeclList *list , AstSpeci *speci)
		{
			this->storage_class =  str_class;
			this->type_qual = typeq; 
			this->list  = list ; 
			this->speci = speci; 
		}
		void Visit() 
		{
			
		}
	
};
#endif 

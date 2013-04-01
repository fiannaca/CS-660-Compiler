#ifndef _AST_STRUCTSPEC_
#define _AST_STRUCTSPEC_
#include "Ast.h"
class AstStructUniSpeci: public AST 
{
	
	string structOrUnion; 
	string structName;
	AstStructDeclList *sdlist; 
	public:
		AstStructSpeci(string structOrUnion ,  string sName  , AstStructDeclList *sdlist)
		{
		    this->structOrUnion = structOrUnion ; 
			this->structName = sName;
		    this->sdlist = sdlist; 
		    
		}
		void Visit() 
		{
			
		}
	
};
#endif 

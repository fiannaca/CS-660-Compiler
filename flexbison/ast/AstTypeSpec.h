#ifndef _AST_TYPESPEC_
#define _AST_TYPESPEC_
#include "Ast.h"
class AstTypeSpeci: public AST 
{
	
	string stypeName;
	AstStructSpeci *stspeci ; 
	AstUnionSpeci *unspeci; 
	public:
		AstTypeSpeci(string stypeName , AstStruct *stspeci , AstUnionSpeci *unspeci)
		{
		    this->stspeci = stspeci;
		    this->unspeci = unspeci; 
		    this->stypeName = stypeName; 
		    
		}
		void Visit() 
		{
			
		}
	
};
#endif 

#ifndef _AST_EXTDEC_
#define _AST_EXTDEC_
#include "Ast.h"
#include "AstFuncDef.h"
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
#endif 
